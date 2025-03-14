Shared project between [42 Le Havre](https://42lehavre.fr/en/homepage-en/) and [Asadhar](https://esadhar.fr/fr/lecole-superieure-dart-design-havre-rouen-0). Using Arduinos Nano BLE 33, the objective was to make a "physical" AI, one that could interact with the physical world, within 5 days. The fun challenge added was that the AI needed to represent a mental ilness; My partner and I chose paranoia, based around the concept of personnal spaces.

The project needed only bases due to the collaboration with non-programmers, but developped many other skills, notably the use of electronics, embeded device programmation, LLM uses, artistic expression, and collaborative effort.

# Artistic expression

![image](https://github.com/user-attachments/assets/f7498ffc-b352-43fc-bc55-200783991900) 
> Connecting the sensors to the arduino

![image](https://github.com/user-attachments/assets/a826167c-d6f3-495a-ac72-7f3ed5134d6e)
> Assembling the sensors into a wooden cube

![IMG_1730](https://github.com/user-attachments/assets/08bb3ed7-be35-481b-a614-ba5b665b6b09)
![IMG_1728](https://github.com/user-attachments/assets/b3da9b79-222f-4d16-bb84-a92a3e6e80f0)
> Final result of the cube

## Pins and wiring
You'll need 6 HC-SR04. 
* Plug all VCC wires from the sensor in series toward the VIN pin of the Arduino.
* Plug all GND wires from the sensor in series toward one of the GND pin of the Arduino.
* Plug the BOTTOM sensor : TRIGG to D12, ECHO to D11
* Plug the TOP sensor : TRIGG to D10, ECHO to D9
* Plug the RIGHT SIDE sensor : TRIGG to D8, ECHO to D7
* Plug the FRONT FACE sensor : TRIGG to A0, ECHO to A1
* Plug the LEFT FACE sensor : TRIGG to A2, ECHO to A3
* Plug the BACK FACE sensor : TRIGG to A4, ECHO to A5
![Pasted image-min](https://github.com/user-attachments/assets/05fcca53-d61c-4d7e-bf5c-ace5d70a58d2)


## Requirements
Python and python packages :
* Python : 3.13.0
* requests : 2.32.3
* pyserial : 3.5
* gTTS : 2.5.4
* pyglet : 2.1.3

As for the Arduino, we'll need the following packages :
* Arduino_LSM9DS1 : 1.1.1
* Arduino_APDS9960 : 1.0.4

## Launching

Connect the Arduino to your computer, and check which USB port it is using. If it's not using `/dev/ttyACM0`, you'll need to change `SERIAL_PORT` in `server.py`. 

Furthermore, in the same folder as `server.py`, you'll need to create a `.env` and put in the following value : `KEY="your_api_key"`. You can use a Key for DeepSeek. If you wish to use another model, you'll need to change the `querry()` function. 

Once connected, simply launch the server with python : `python3 server.py`. If it works, you'll see a `Listening on /dev/ttyACM0 ...` in the console.

## Known issues
The TTS is overlapping with the next one, and sometimes repeating the same audio file.
