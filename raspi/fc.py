#!flask/bin/python
from flask import Flask,render_template, request
import datetime
import time
import RPi.GPIO as GPIO
app = Flask(__name__)

GPIO.setmode(GPIO.BCM)

# Create a dictionary called pins to store the pin number, name, and pin state:
pins = {
   14 : {'name' : 'living room', 'state' : GPIO.HIGH},
   11 : {'name' : 'dining room', 'state' : GPIO.HIGH},
   10 : {'name' : 'office', 'state' : GPIO.HIGH},
   9 : {'name' : 'bedroom', 'state' : GPIO.HIGH},

   2 : {'name' : 'fan high', 'state' : GPIO.HIGH},
   3 : {'name' : 'fan medium', 'state' : GPIO.HIGH},
   4 : {'name' : 'fan low', 'state' : GPIO.HIGH},
   7 : {'name' : 'fan off', 'state' : GPIO.HIGH},
   8 : {'name' : 'light', 'state' : GPIO.HIGH}
   }

# Set each pin as an output and make it low:
for pin in pins:
   GPIO.setup(pin, GPIO.OUT)
   GPIO.output(pin, GPIO.HIGH)

# Make sure fan is off
GPIO.output(4, GPIO.LOW)
GPIO.output(7, GPIO.LOW)
time.sleep(.3)
GPIO.output(7, GPIO.HIGH)
GPIO.output(4, GPIO.HIGH)
time.sleep(.3)

@app.route("/")
def main():
   templateData = {
      'pins' : pins
   }
   return render_template('main.html', **templateData)

@app.route("/<changePin>/<action>")
def action(changePin, action):
   changePin = int(changePin)
   settingName = pins[changePin]['name']
   if action == "toggle":
      message = "Toggle state for " + settingName + "."
      # Reset all fans
      GPIO.output(9, GPIO.HIGH)
      GPIO.output(10, GPIO.HIGH)
      GPIO.output(11, GPIO.HIGH)
      GPIO.output(14, GPIO.HIGH)
      time.sleep(.3)
      GPIO.output(10, GPIO.LOW)
      time.sleep(.3)

      GPIO.output(changePin, GPIO.LOW)
      time.sleep(.3)
      GPIO.output(changePin, GPIO.HIGH)

   templateData = {
      'message' : message,
      'pins' : pins
   }

   return render_template('main.html', **templateData)

if __name__ == "__main__":
   try:   
      app.run(host='0.0.0.0', port=8080, debug=True)
   except KeyboardInterrupt:
      GPIO.cleanup()

