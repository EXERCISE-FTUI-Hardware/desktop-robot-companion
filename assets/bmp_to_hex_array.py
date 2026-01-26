import sys

from PIL import Image

def main():
    if (len(sys.argv) < 1):
        print("Please supply a file as an argument.")
        return
    
    filename = sys.argv[1]
    
    with Image.open(filename) as image:
        image_bytes = image.tobytes();
        first = True
        
        print("{", end = "")
        
        for byte in image_bytes:
            if (not first):
                print(",", end = "")
            else:
                first = False
                
            print(f"0x{byte:02x}", end = "")
            
        print("}", end = "")

if (__name__ == "__main__"):
    main()