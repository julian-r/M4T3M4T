import serial
import datetime

def main():
    ser = serial.Serial('/dev/ttyACM0', 115200)
    while 1:
        print datetime.datetime.now().isoformat(), ser.readline(),

if __name__ == '__main__':
    main()
