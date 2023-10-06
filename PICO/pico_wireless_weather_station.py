import board
import busio
import adafruit_dht
import adafruit_bmp.BMP085_I2C

# Initialize I2C bus and BMP180 sensor
i2c = busio.I2C(board.SCL, board.SDA)
bmp = adafruit_bmp.BMP085_I2C(i2c)

# Initialize DHT11 sensor
dht = adafruit_dht.DHT11(board.D4)

# Define the raindrop sensor pin
raindrop_pin = board.D5  # Change this to your specific pin

# Function to read raindrop sensor
def read_raindrop():
    return digitalio.DigitalInOut(raindrop_pin).value

# Main loop
while True:
    try:
        temperature = dht.temperature
        humidity = dht.humidity
        pressure = bmp.pressure

        raindrop_value = read_raindrop()

        print(f"Temperature: {temperature} °C")
        print(f"Humidity: {humidity}%")
        print(f"Pressure: {pressure} hPa")
        print(f"Raindrop: {'Detected' if raindrop_value else 'Not Detected'}")
    
    except Exception as e:
        print(f"Error: {e}")

    time.sleep(2)  # Delay for 2 seconds before taking the next reading
