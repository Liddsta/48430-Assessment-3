# Plan for the group assignment
    1. find (or make up) a client (apparently we don't actually need one its just "suggested")
    2. inject as many algorithms into the project as possible (so far, RSA,  huffman codes, some form of both sort and search for the contacts)
    3. put each algorithm in a separate library (header file)
    4. profit?


## possible ideas:
- client side attachment and/or message encryption and compression service for secure messaging
    - Will do:
        - can encrypt or decrypt messages or files for sending or recieving with RSA public private key pairs
        - can store your private key (password protected) and the public keys of your contacts (freetext) for easy access with other contact information
        - command line interface for ease of use
    - Won't do:
        - actual messaging (we don't have the libraries for it and i'm not writing those from scratch)
    - modules:
        - Command line interface
            - List the options in each section of the menu
            - Accept an input to choose which option (i suggest using numbers)
            - Take string input when necessary
            - Run the other modules
        - RSA
            - RSA encrypt
            - RSA decrypt
            - RSA key password protect
            - RSA key gain access with passsword (rename for later)
        - Contacts
            - Create contact
            - Access contact
            - Modify contact
            - Encrypyt for sending to contact
            - Decrypt message from contact
            - store contact to file(s) for persistence
            - STRETCH GOALS
            - maybe hash map for runtime
            - implement multiple sorting algorithms
            - Fuzzy finder??
        - Compression (huffman coding if possible)
            - Lossless compression for text (before or after encryption? both?)
            - Optional lossy encryption for images (before encryption), then lossless compression (once again before or after encryption... i think both why not)
            - Reverse lossless compression
