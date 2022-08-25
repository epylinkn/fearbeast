import RPi.GPIO as GPIO
import threading
import time

class Trigger:
    def __init__(self, audio, lights):
        self.audio = audio
        self.lights = lights
        
        # GPIO STUFF IS TEMPORARY UNTIL THE PRESSURE PADS COME IN OR IF WE DO ARDUINO AND IT SENDS THE PINUP SIGNAL
        GPIO.setwarnings(False) # Ignore warning for now
        GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
        GPIO.setup(10, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)

        # Start a listener thread as to not block up the rest of the software
        l = threading.Thread(target=self.listen, args=())
        l.start()
    
    def listen(self):
        print("starting listen")
        self.audio.play("SCP-x3x.wav")
        # "active" boolean used to gate the trigger
        active = False
        while True:
            if GPIO.input(10) == GPIO.HIGH:
                if not active:
                    print("Button was pushed!")
                    active = True
                    self.audio.play("TheParting.wav")
                    self.lights.light_fade(True)
                    time.sleep(1)
            if GPIO.input(10) != GPIO.HIGH:
                if active:
                    print("Button was released")
                    active = False
                    self.audio.play("SCP-x3x.wav")
                    self.lights.light_fade(False)
                    # self.lights.deactivate()
                    time.sleep(1)
                    
            # time.sleep(10)
            # time.sleep(10)

            # events = pygame.event.get()
            # for event in events:
            #     print(f"events {event}")
            #     if event.type == pygame.KEYDOWN:
            #         if event.key == pygame.K_UP:
            #             print("space down")
            #             self.audio.play("TheParting.wav")
            #     if event.type == pygame.KEYUP:
            #         if event.key == pygame.K_UP:
            #             print("space up")
            #             self.audio.play("SCP-x3x.wav")
