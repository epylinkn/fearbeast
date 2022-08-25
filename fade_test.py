import pygame

pygame.mixer.init()
pygame.init()

# Maybe you can subclass the pygame.mixer.Sound and
# add the methods below to it..
class Fader(object):
    instances = []
    def __init__(self, fname):
        super(Fader, self).__init__()
        assert isinstance(fname, basestring)
        self.sound = pygame.mixer.Sound(fname)
        self.increment = 0.01 # tweak for speed of effect!!
        self.next_vol = 1 # fade to 100 on start
        Fader.instances.append(self)

    def fade_to(self, new_vol):
        # you could change the increment here based on something..
        self.next_vol = new_vol

    @classmethod
    def update(cls):
        for inst in cls.instances:
            curr_volume = inst.sound.get_volume()
            # print inst, curr_volume, inst.next_vol
            if inst.next_vol > curr_volume:
                inst.sound.set_volume(curr_volume + inst.increment)
            elif inst.next_vol < curr_volume:
                inst.sound.set_volume(curr_volume - inst.increment)

sound1 = Fader("TheParting.wav")
sound2 = Fader("SCP-x3x.wav")
sound1.sound.play()
sound2.sound.play()
sound2.sound.set_volume(0)

# fading..
sound1.fade_to(0)
sound2.fade_to(1)


while True:
    Fader.update() # a call that will update all the faders..