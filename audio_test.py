import pygame
from gpiozero import Button
from time import sleep

button_gpio = 21

button = Button(button_gpio, pull_up=False)

mode = ""
active = False




def button_released():
    print("Button not pushed")
    fadeOut
    playBeastMusic
    playMusic
    active = False
    
def button_pressed():
    print("Button was pushed!")
    fadeOut
    playChildMusic
    playMusic
    active = True

# def setup():
button.when_pressed = button_pressed
button.when_released = button_released
# GPIO.setmode(GPIO.BOARD)
# GPIO.setup(10, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)

# GPIO.input(31)
pygame.mixer.pre_init(44100, -16, 1, 2048)
pygame.init()
pygame.mixer.init()
childMusic = pygame.mixer.Sound("TheParting.wav")
beastMusic = pygame.mixer.Sound("SCP-x3x.wav")
fadeOut = pygame.mixer.fadeout(2000)

playChildMusic = pygame.mixer.Sound.play(childMusic, loops=-1, maxtime=0, fade_ms=2000)
playBeastMusic = pygame.mixer.Sound.play(beastMusic, loops=-1, maxtime=0, fade_ms=2000)

def init():
    playBeastMusic
    while True:
        if GPIO.input(10) == GPIO.HIGH:
            if not active:
                print("Button was pushed!")
                fadeOut
                # childMusic
                playChildMusic
                active = True
            else:
                pass
        else:
            if active:
                print("Button not pushed")
                fadeOut
                # beastMusic
                playBeastMusic
                active = False

# setup()
init()
