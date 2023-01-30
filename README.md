# fearbeast

- Raspberry Pi python app controls DMX lighting
- Teensy monitors pressure mats and controls sound
- UNO controls the LEDs


Honestly, this entire setup is extremely overkill. In the next iteration just use the Teensy. You can also just do the DMX from the Teensy.
- Drop the UNO. The UNO was required because I didn't have a way to shift the teensy voltage (3.3V -> 5V) for our LEDs. It came with the setup from J. In addition, the code for the UNO is a complete mess because it only has one Serial port and so it was easier to send data over 4 pins... so I could keep the Serial port open for uploading / debugging.
- Raspberry Pi for DMX lighting is pretty painful. Pi USB startup scripts are notoriously finicky -- e.g. /dev/<random>. It's not a bad option for playa, though bring your own networking router and keyboard!!!! (I forgot to pack my own and had to hunt all over playa...)
- Added Teensy over Pi for audio quality concerns.


# Develop

```
sudo -E python3 init.py
```

# Deploy

```
./sync.sh
```

# Authors

- Jerome
- LEAFCRUNCHER (@epylinkn)
