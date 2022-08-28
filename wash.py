
from DMXEnttecPro import Controller

dmx = Controller('/dev/ttyUSB1')  # Typical of Linux
for c in range(512):
    dmx.set_channel(c, 255)  # Sets DMX channel 1 to max 255
dmx.submit()  # Sends the update to the controller
