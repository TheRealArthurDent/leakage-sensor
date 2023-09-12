#include "app.hpp"

#include "Arduino.h"
#include "led.h"
#include "wifi-connection.hpp"
#include "ota-handler.hpp"
#include "mqtt-client.hpp"
#include "alert.hpp"
#include "debug.h"

#include <string>

App::App() : metronome(Metronome(LOOP_DURATION)),
             masterCaution(MasterCaution()),
             mqttClient(MqttClient()),
             waterLevelSensor(WaterSensor(A0, D1)),
             leakageSensor(WaterSensor(A0, D2)),
             waterLevelAlert("waterLevel", &masterCaution),
             leakageAlert("leakage", &masterCaution)
{
}

void App::setup()
{
    initDebugging();

    // pinMode(led_built_in_ESP, OUTPUT);
    // pinMode(led_built_in_Node, OUTPUT);
    // digitalWrite(led_built_in_Node, HIGH);
    // digitalWrite(led_built_in_ESP, HIGH);

    // buzzer
    pinMode(BUZZER, OUTPUT);

    // RGB LED
    pinMode(RGB_LED_GREEN, OUTPUT);
    pinMode(RGB_LED_RED, OUTPUT);

    mqttClient.init();

    std::list<WifiDependent *> deps;
    deps.push_back(&OtaHandler::getInstance());
    deps.push_back(&mqttClient);

    WifiConnection::getInstance().init(deps);
}

void App::loop()
{
    // TODO
    // measure
    int waterLevel = waterLevelSensor.getLevel();
    mqttClient.publish("leakageSensor/waterLevel/rawValue", std::to_string(waterLevel));
    // trigger/silence alerts
    if (waterLevel > THRESHOLD_WATERLEVEL)
    {
        waterLevelAlert.activate("Tank full! Water level is " + std::to_string(waterLevel) + ". Threshold value is " + std::to_string(THRESHOLD_WATERLEVEL));
    }
    else
    {
        waterLevelAlert.clear();
    }

    // measure
    int leakage = leakageSensor.getLevel();
    mqttClient.publish("leakageSensor/leakage/rawValue", std::to_string(leakage));
    // trigger/silence alerts
    if (leakage > THRESHOLD_LEAKAGE)
    {
        leakageAlert.activate("!!!!! WATER IS LEAKING !!!!!");
    }
    else
    {
        leakageAlert.clear();
    }

    std::vector<Alert *> alerts = masterCaution.getAllAlerts();
    std::for_each(alerts.begin(), alerts.end(), [this](Alert *a)
                  {
                      std::string baseTopic = "leakageSensor/" + a->getName() + "/alert";
                      mqttClient.publish(baseTopic + "/active", a->isActive() ? "1" : "0");
                      mqttClient.publish(baseTopic + "/message", a->getMessage());
                      //
                  });

    // activate buzzer based on alert state
    if (masterCaution.isAlarming())
    {
        // RGB LED RED
        analogWrite(RGB_LED_GREEN, 0);
        analogWrite(RGB_LED_RED, 255);

        // BUZZER
        digitalWrite(BUZZER, HIGH);
        delay(2000);
        digitalWrite(BUZZER, LOW);
    }
    else if (masterCaution.isAcknowledged())
    {
        // RGB LED YELLOW
        analogWrite(RGB_LED_GREEN, 100);
        analogWrite(RGB_LED_RED, 100);
    }
    else
    {
        // RGB LED GREEN
        analogWrite(RGB_LED_GREEN, 150);
        analogWrite(RGB_LED_RED, 0);
    }

    metronome.waitForNextCycle();
    OtaHandler::getInstance().handleUpload();
}