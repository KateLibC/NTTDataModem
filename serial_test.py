import serial
import time

port = 'COM7'


class modem(object):
    def __init__(self, port, baudrate=9600):
        self.port = port
        self.baudrate = baudrate
        self.interface = None
        self.listening = False
        self._createInterface()

    def _createInterface(self):
        self.interface = serial.Serial(self.port, baudrate=self.baudrate, timeout=0)

    def _destroyInterface(self):
        if self.interface and self.interface.isOpen():
            self.interface.close()
            self.interface = None
            self.listening = False

    def escape(self):
        time.sleep(1)
        self.interface.write('+++')
        time.sleep(1)

    def listen(self):
        cmds = ['AT+FCLASS=8', 'AT+VLS=1', 'AT+VSM=1,8000', 'AT+VTX']
        self.reset()
        self.writeModem(writes=cmds, response=True)

    def hangup(self):
        cmds = ['\0{}{}'.format(chr(0x10), chr(0x03))]
        self.writeModem(writes=cmds)
        self.escape()
        self.onhook()
        self.listening = False
        self.reset()

    def onhook(self):
        cmds = ['ATH0']
        self.writeModem(writes=cmds)

    def reset(self):
        cmds = ['ATZ0', 'ATE0']
        self.writeModem(writes=cmds)

    def readModem(self, timeout):
        t = time.time()
        while True:
            if t - time.time() >= timeout:
                break
            r = self.interface.readline().strip()
            if r:
                print(r)

    def writeModem(self, writes, timeout=60, response=False):
        if type(writes) is str:
            writes = [writes]
        for write in writes:
            write = f'{write}\r\n'.encode('ascii')
            write = bytes(write)
            self.interface.write(write)
            if response:
                return self.readModem(timeout=timeout)

if __name__ == '__main__':
    m = modem(port=port)
    m.listen()
    time.sleep(10)