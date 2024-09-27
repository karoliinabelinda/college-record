
from playrobot import Servo
import RPi.GPIO as GPIO
import time

Servo.startServo(0x60)            #馬達的I2C位址
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

#5路循跡模組腳位定義
PORT_A=23   #GREEN  Center
PORT_B=22   #YELLO  Left_1
PORT_C=5    #BLUE   Right_1
PORT_D=27   #ORANGE Left_2
PORT_E=6    #PURPLE Right_2
pin_to_circuit = 4
TRIG = 19
ECHO = 16
PIN = 26
GPIO.setup(pin_to_circuit, GPIO.IN)
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)

GPIO.setmode(GPIO.BCM)
GPIO.setup(PORT_D,GPIO.IN)  
GPIO.setup(PORT_B,GPIO.IN)  
GPIO.setup(PORT_A,GPIO.IN)  
GPIO.setup(PORT_C,GPIO.IN)   
GPIO.setup(PORT_E,GPIO.IN)

def get_distance():
    GPIO.output(TRIG,0)
    time.sleep(0.0001)
    GPIO.output(TRIG,1)
    time.sleep(0.0001)
    GPIO.output(TRIG,0)
    while GPIO.input(ECHO)==0:
        start = time.time()
    while GPIO.input(ECHO)==1:
        end = time.time()
    return (end - start)*17241

GPIO.setmode(GPIO.BCM)
GPIO.setup(PIN,GPIO.IN,GPIO.PUD_UP)
print('IRM Test Start ...')

while True:
        status = GPIO.input(pin_to_circuit)
        if status == 0:
            break
        else:
            print(1)
        time.sleep(1)

while True:
        Servo.setServoPulse(0,1400)
        Servo.setServoPulse(1,2700)
        time.sleep(0.5)
        break

while True:

        d = GPIO.input(PORT_D) #Left 02
        b = GPIO.input(PORT_B) #Left 01
        a = GPIO.input(PORT_A)
        c = GPIO.input(PORT_C) #Right 01
        e = GPIO.input(PORT_E) #Right 02

        if a == 0 and b == 0 and c == 0:
            if e == 0 and d == 0:
                Servo.setServoPulse(0,1595)
                Servo.setServoPulse(1,1590)
                time.sleep(0.1)
                Servo.setServoPulse(0,0)  #stop
                Servo.setServoPulse(1,0)
                time.sleep(0.1)
                break

        if a == 1 and b == 1 and c == 1:
            if e == 0 and d == 0:
                Servo.setServoPulse(0,1400)
                Servo.setServoPulse(1,2700)
                
        if a == 0 and b == 0 and c == 0:
            Servo.setServoPulse(0,1595)
            Servo.setServoPulse(1,2300)
        if c == 0 and d == 0:
            Servo.setServoPulse(0,1400)
            Servo.setServoPulse(1,2700)
        if a == 0 and e == 0:
            Servo.setServoPulse(0,1400)
            Servo.setServoPulse(1,2700)
        if a == 0 and b == 0:
            Servo.setServoPulse(0,1400)
            Servo.setServoPulse(1,2700)
        if a == 0 and d == 0 and e == 0:
            if c == 0 and b ==0:
                Servo.setServoPulse(0,1400)
                Servo.setServoPulse(1,2700)
        if a == 0 and b == 0 and e == 0:
            Servo.setServoPulse(0,1400)
            Servo.setServoPulse(1,2700)
        if b == 0 and c == 0 and d == 0 :
            Servo.setServoPulse(0,1400)
            Servo.setServoPulse(1,2700)
        if e == 0 and d == 0:
            Servo.setServoPulse(0,1595)
            Servo.setServoPulse(1,1590)
        if a == 0 and b == 0 and c == 0 and d == 0 and e == 0:
            Servo.setServoPulse(0,1595)
            Servo.setServoPulse(1,1590)
        if a == 0 and b == 0 and c == 0 and d == 0:
            Servo.setServoPulse(0,1595)
            Servo.setServoPulse(1,2300)
            
        if e == 0:
            Servo.setServoPulse(0,1595)
            Servo.setServoPulse(1,2700)
        if c == 0:
            Servo.setServoPulse(0,1595)
            Servo.setServoPulse(1,2300)
        if a == 0:
            Servo.setServoPulse(0,1200)
            Servo.setServoPulse(1,1800)
        if b == 0:
            Servo.setServoPulse(0,1400)
            Servo.setServoPulse(1,1590)
        if d == 0:
            Servo.setServoPulse(0,1400)
            Servo.setServoPulse(1,1590)

while True:
    if GPIO.input(PIN) == 0:
        count = 0 
        while GPIO.input(PIN) == 0 and count < 300:  #9ms
            count += 1
            time.sleep(0.00006)

        count = 0 
        while GPIO.input(PIN) == 1 and count < 80:  #4.5ms
            count += 1
            time.sleep(0.00006)

        idx = 0 
        cnt = 0 
        data = [0,0,0,0]
        for i in range(0,32):
            count = 0 
            while GPIO.input(PIN) == 0 and count < 15:    #0.56ms
                count += 1
                time.sleep(0.00006)

            count = 0 
            while GPIO.input(PIN) == 1 and count < 40:   #0: 0.56mx
                count += 1                               #1: 1.69ms
                time.sleep(0.00006)

            if count > 8:
                data[idx] |= 1<<cnt
            if cnt == 7:
                cnt = 0
                idx += 1
            else:
                cnt += 1
                

        if data[2] == 0x18:   #2
            Servo.setServoPulse(0,1400)  #straight
            Servo.setServoPulse(1,2700)
            time.sleep(0.3)
            Servo.setServoPulse(0,1595)
            Servo.setServoPulse(1,1590)
            time.sleep(0.1)
        if data[2] == 0x0c:    #1
            Servo.setServoPulse(0,1400)  #laft
            Servo.setServoPulse(1,1590)
            time.sleep(0.3)
            Servo.setServoPulse(0,1595)
            Servo.setServoPulse(1,1590)
            time.sleep(0.1)
      
        if data[2] == 0x5e: #3
            Servo.setServoPulse(0,1595)  #right
            Servo.setServoPulse(1,2300)
            time.sleep(0.2)
            Servo.setServoPulse(0,1595)
            Servo.setServoPulse(1,1590)
            time.sleep(0.1)

        if data[2] == 0x1c:     #5
            Servo.setServoPulse(0,1400)  #stop
            Servo.setServoPulse(1,2700)
            time.sleep(0.2)
            Servo.setServoPulse(0,0)  #stop
            Servo.setServoPulse(1,0)
            time.sleep(0.1)
            break


while True:
    

    d = GPIO.input(PORT_D) #Left 02
    b = GPIO.input(PORT_B) #Left 01
    a = GPIO.input(PORT_A)
    c = GPIO.input(PORT_C) #Right 01
    e = GPIO.input(PORT_E) #Right 02
            
    if e == 0:
        Servo.setServoPulse(0,1595)
        Servo.setServoPulse(1,2700)
    if c == 0:
        Servo.setServoPulse(0,1595)
        Servo.setServoPulse(1,2100)
    if a == 0:
        Servo.setServoPulse(0,1200)
        Servo.setServoPulse(1,1800)
    if b == 0:
        Servo.setServoPulse(0,1400)
        Servo.setServoPulse(1,1590)
    if d == 0:
        Servo.setServoPulse(0,1400)
        Servo.setServoPulse(1,1590)
    if 5 < (get_distance()) < 15:
        Servo.setServoPulse(0,1400)  #laft
        Servo.setServoPulse(1,1590)
        time.sleep(1)
        Servo.setServoPulse(0,1595)  #right
        Servo.setServoPulse(1,2300)
        time.sleep(1)
        Servo.setServoPulse(0,1400)  #straight
        Servo.setServoPulse(1,2700)
        time.sleep(1.1)
        Servo.setServoPulse(0,1595)  #right
        Servo.setServoPulse(1,2300)
        time.sleep(1)
        Servo.setServoPulse(0,1400)  #straight
        Servo.setServoPulse(1,2700)
        time.sleep(0.2)
        Servo.setServoPulse(0,1400)  #laft
        Servo.setServoPulse(1,1590)
        time.sleep(1)
        break

while True:
    

    d = GPIO.input(PORT_D) #Left 02
    b = GPIO.input(PORT_B) #Left 01
    a = GPIO.input(PORT_A)
    c = GPIO.input(PORT_C) #Right 01
    e = GPIO.input(PORT_E) #Right 02
            
    if e == 0:
        Servo.setServoPulse(0,1595)
        Servo.setServoPulse(1,2700)
    if c == 0:
        Servo.setServoPulse(0,1595)
        Servo.setServoPulse(1,2100)
    if a == 0:
        Servo.setServoPulse(0,1400)
        Servo.setServoPulse(1,2700)
    if b == 0:
        Servo.setServoPulse(0,1400)
        Servo.setServoPulse(1,1590)
    if d == 0:
        Servo.setServoPulse(0,1400)
        Servo.setServoPulse(1,1590)
    if a == 0 and b == 0 and c == 0:
            if e == 0 and d == 0:
                Servo.setServoPulse(0,1400)
                Servo.setServoPulse(1,2700)
                time.sleep(1)
                Servo.setServoPulse(0,1595)
                Servo.setServoPulse(1,1590)
                break
