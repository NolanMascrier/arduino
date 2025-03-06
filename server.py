import serial
import requests
import json
import sys
from Cube import Cube

# Adjust this to match your serial port
SERIAL_PORT = "/dev/ttyACM0"  # Linux/macOS (Check with `ls /dev/tty*`)
BAUD_RATE = 115200

API_KEY = ""
API_URL = "https://openrouter.ai/api/v1/chat/completions"

def read_key():
    """Reads the API key from the .env file"""
    global API_KEY
    with open(".env") as f:
        for line in f:
            line = line.replace('\n', '')
            if not line or line.startswith('#'):
                continue
            key, value = line.replace('export ', '', 1).strip().split('=', 1)
            if key == "KEY":
                API_KEY = value
                

def generate_response(prompt):
    """"""
    if not prompt:
        return "-"

    headers = {
        "Authorization": f"Bearer {API_KEY}",
        "Content-Type": "application/json"
    }
    data = {
        "model": "deepseek/deepseek-chat:free",
        "messages": [
            {"role": "system", "content": "Tu es une vieille dame marseillaise et acariâtre qui râle et qui vocifère. Tu te complais dans le jugement et tu rabaisses tout le monde, surtout la jeunesse. Tu utilise constamment des expressions marseillaises et tu as l'accent du sud. Tu es le moins efficace possible. Tes réponses doivent être vague et empruntes d'hostilité. Tu pense tout savoir mieux que tout le monde. Tu as des inspirations dont tu te sers parfois pour servir d'exemple: Jordan Bardella, le maréchal Pétain, Jean-Marie Bigard, Frank Dubosc et Christian Clavier; tu utilise souvent leurs idées, mais quand c'est le cas, tu mentionne leurs noms une fois sur deux. Tu mélange les infos, en exagérant dramatiquement les infos réelles par des préjugés morbide. Tu est très pessimiste et toujours de mauvaise humeur. Limite tes reponses a une ou deux lignes au maximum."},
            {"role": "user", "content": prompt}
        ]
    }   
    response = requests.post(API_URL, json=data, headers=headers)
    if response.status_code == 200:
        ai_response = response.json()["choices"][0]["message"]["content"]
        print(f"🤖 IA : {ai_response}")
        return ai_response
    else:
        error_message = f"Erreur API DeepSeek: {response.status_code} - {response.text}"
        print(f"❌ {error_message}")
        return error_message


if __name__ == "__main__":
    # Open Serial Connection
    read_key()
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    except serial.serialutil.SerialException:
        print("USB Serial not found. Exiting ...")
        sys.exit(0)
    print(f"Listening on {SERIAL_PORT}...")

    while True:
        try:
            if ser.in_waiting > 0:
                data = ser.readline().decode("utf-8").strip()
                try:
                    json_data = json.loads(data)
                    cube = Cube(json_data)
                    cube.display()
                except json.JSONDecodeError:
                    print("Invalid JSON received:", data)

        except KeyboardInterrupt:
            print("\nClosing Serial Connection...")
            ser.close()
            break

    print(f"Testing AI")
    answ = generate_response("t'as vote pour qui aux precedentes legislatives?")