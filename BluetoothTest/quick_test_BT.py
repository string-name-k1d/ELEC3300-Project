# @Simple test for send/receive

import socket
import serial

bt_addr = '98:d3:02:96:a0:16'
serial_port = 'COM4'

s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)

send = serial.Serial(
    # port='COM4',  # Change this to your COM port
    port = serial_port
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1 # Timeout in seconds for read operations
)

s.connect((bt_addr, 1))

_recv = bytearray(1)

_input = ""
while (_input != "exit"):
    s.recv_into(_recv, 1)
    print(_recv)
    send.write(_recv)

    # s.send("Hello")
    # send.write(_input.encode("ascii"))

    # _input = input("Input sth: ")

send.close()
s.close()