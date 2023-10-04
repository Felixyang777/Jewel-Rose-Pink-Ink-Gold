#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(2, 3);  // RX,TX(UNO)


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

void setup() {
    Serial.begin(9600);
    while (!Serial)
        ;  // For Yun/Leo/Micro/Zero/...
    delay(100);
    Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

    // set the data rate for the sensor serial port
    finger.begin(57600);

    if (finger.verifyPassword()) {
        Serial.println("Found fingerprint sensor!");
    }
    else {
        Serial.println("Did not find fingerprint sensor :(");
        while (1) { delay(1); }
    }
}

uint8_t readnumber(void) {
    uint8_t num = 0;

    while (num == 0) {
        while (!Serial.available())
            ;
        num = Serial.parseInt();
    }
    return num;
}

void loop()  // run over and over again
{
    getFingerprintIDez();
    delay(50);  //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
    uint8_t p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
    case FINGERPRINT_NOFINGER:
        Serial.println("No finger detected");
        return p;
    case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return p;
    case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        return p;
    default:
        Serial.println("Unknown error");
        return p;
    }

    // OK success!

    p = finger.image2Tz();
    switch (p) {
    case FINGERPRINT_OK:
        Serial.println("Image converted");
        break;
    case FINGERPRINT_IMAGEMESS:
        Serial.println("Image too messy");
        return p;
    case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return p;
    case FINGERPRINT_FEATUREFAIL:
        Serial.println("Could not find fingerprint features");
        return p;
    case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Could not find fingerprint features");
        return p;
    default:
        Serial.println("Unknown error");
        return p;
    }

    // OK converted!
    p = finger.fingerFastSearch();
    if (p == FINGERPRINT_OK) {
        Serial.println("Found a print match!");
    }
    else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println("Communication error");
        return p;
    }
    else if (p == FINGERPRINT_NOTFOUND) {
        Serial.println("Did not find a match");
        return p;
    }
    else {
        Serial.println("Unknown error");
        return p;
    }

    // found a match!
    Serial.print("Found ID #");
    Serial.print(finger.fingerID);
    Serial.print(" with confidence of ");
    Serial.println(finger.confidence);

    return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK) return -1;

    p = finger.image2Tz();
    if (p != FINGERPRINT_OK) return -1;

    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK) return -1;

    // found a match!
    Serial.print("Found ID #");
    Serial.print(finger.fingerID);
    Serial.print(" with confidence of ");
    Serial.println(finger.confidence);
    return finger.fingerID;
}
