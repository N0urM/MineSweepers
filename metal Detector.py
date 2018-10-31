import RPi.GPIO as GPIO
import time 

GPIO.setmode(GPIO.BOARD)

metalPin = 36
Trig = 40
echo = 38

GPIO.setup (Trig , GPIO.OUT)
GPIO.setup (echo , GPIO.IN)
GPIO.setup (metalPin , GPIO.IN)

print ("Hello Echo !")
time.sleep (0.1)

def measure () :    

    GPIO.output (Trig , True)
    time.sleep (0.00001)
    GPIO.output (Trig , False)

    start = time.time ()
    end = time.time()


    while GPIO.input (echo) == False :
        start = time.time()

    while GPIO.input (echo) == True :
        end = time.time()

    d =  ( ( end - start ) * 34300 ) /2
    
    return d

def measureAvg ():
    d1 = measure()
    time.sleep (0.1)
    d2 = measure()
    time.sleep (0.1)
    d3 = measure()
    time.sleep (0.1)

    avg = (d1 + d2 + d3 )/3
    return avg


while (True):
    if GPIO.input(metalPin) :
        print ("Metal detected")
        avg = measureAvg()

        if avg > 10 :
            print ('buried mine')
        else :
            print ('surface mine')

        time.sleep (0.5)
        
    else :
        print ("Clear !!")
        time.sleep (0.5)
        
GPIO.cleanup()
