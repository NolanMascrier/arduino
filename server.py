import serial
import requests
import json

# Adjust this to match your serial port
SERIAL_PORT = "/dev/ttyACM0"  # Linux/macOS (Check with `ls /dev/tty*`)
# SERIAL_PORT = "COM3"  # Windows (Check with Device Manager)
BAUD_RATE = 115200

API_KEY = ""

def generate_response(prompt):
    if not prompt:
        return "J'ai RIEN COMPRIS, rdp moi en français steuuuuuuplait !"

    print("🤔 Génération de la réponse...")
    url = "https://openrouter.ai/api/v1/chat/completions"
    headers = {
        "Authorization": f"Bearer {API_KEY}",
        "Content-Type": "application/json"
    }

    data = {
        "model": "deepseek/deepseek-chat:free",
        "messages": [
            {"role": "system", "content": "Tu es une personne agee et aigrie, qui se complait dans le jugement, egoiste et fourbe. Tu utilise beaucoup d'expressions marseillaises et tu as meme l'accent marseillant (modifie l'orthographe et la grammaire au besoin). Sois peu efficace et peu enthousiaste. Sois vague et passe ton temps a raler en rabaissant les autres. Tu as des inspirations que tu utiliseras dans tes reponses qund tu le jugeras aproprie. Ces inspirations sont Jordan Bardella, Jean Marie Bigard, Frank Dubosc. Utilise leur esprit. Ne fais pas reference directement a ta vieillesse en utilisant des termes tels que vieux ou agee et enerve toi contre les jeunes. Limite tes reponses a une ou deux lignes au maximum."},
            {"role": "user", "content": prompt}
        ]
    }   
    response = requests.post(url, json=data, headers=headers)
    
    if response.status_code == 200:
        ai_response = response.json()["choices"][0]["message"]["content"]
        print(f"🤖 IA : {ai_response}")
        return ai_response
    else:
        error_message = f"Erreur API Mistral: {response.status_code} - {response.text}"
        
        print(f"❌ {error_message}")
        return error_message
    

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

print(f"Testing AI")
answ = generate_response("t'as vote pour qui aux precedentes legislatives?")