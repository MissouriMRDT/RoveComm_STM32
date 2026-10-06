import socket
import sys

# STM32 Board Network Configuration
BOARD_IP = "198.162.0.10"
PORT = 5000

def send_command(command):
    # Create UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.settimeout(2.0)
    
    try:
        print(f"Sending '{command}' to {BOARD_IP}:{PORT}...")
        sock.sendto(command.encode('utf-8'), (BOARD_IP, PORT))
        print("Packet sent successfully!")
    except Exception as e:
        print(f"Error sending packet: {e}")
    finally:
        sock.close()

if __name__ == "__main__":
    if len(sys.argv) < 2 or sys.argv[1].upper() not in ["ON", "OFF"]:
        print("Usage: python control_led.py [ON|OFF]")
        print("Example: python control_led.py ON")
        sys.exit(1)

    cmd = f"LED_{sys.argv[1].upper()}"
    send_command(cmd)