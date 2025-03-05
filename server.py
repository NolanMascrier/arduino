import serial
import requests
import json

# Adjust this to match your serial port
SERIAL_PORT = "/dev/ttyACM0"  # Linux/macOS (Check with `ls /dev/tty*`)
# SERIAL_PORT = "COM3"  # Windows (Check with Device Manager)
BAUD_RATE = 115200
SERVER_URL = "http://127.0.0.1:8080"  # Change to your server's IP if needed

# Open Serial Connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
print(f"Listening on {SERIAL_PORT}...")

while True:
    try:
        if ser.in_waiting > 0:
            data = ser.readline().decode("utf-8").strip()
            print("Received:", data)

            # Validate JSON
            try:
                json_data = json.loads(data)
                # Send data to HTTP server
                print("Server response:", json_data)
            except json.JSONDecodeError:
                print("Invalid JSON received:", data)

    except KeyboardInterrupt:
        print("\nClosing Serial Connection...")
        ser.close()
        break