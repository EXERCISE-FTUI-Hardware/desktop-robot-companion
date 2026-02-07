import os

def main():
    header_text = "#ifndef ANIMATIONS_HPP\n#define ANIMATIONS_HPP\n\n#include <Arduino.h>\n\nnamespace Animations {\n"
    
    first = True
    
    for filename in os.listdir("out"):
        if (not filename.endswith(".txt")):
            continue
        
        with open("out/" + filename) as file:
            if (not first):
                header_text += "\n\n"
                
            header_text += "\tstatic const uint8_t PROGMEM "
            header_text += filename.upper().split(".")[0]
            header_text += "[] = "
            header_text += file.read()
            header_text += ";"
                
            first = False
            
    header_text += "\n}\n\n#endif // ANIMATIONS_HPP"
    
    with open("out/header.hpp", "+w") as header_file:
        header_file.write(header_text)

if (__name__ == "__main__"):
    main()