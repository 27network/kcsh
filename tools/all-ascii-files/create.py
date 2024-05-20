# Create a file named <char>.txt for each character in the ASCII table while ignoring errors

for i in range(1, 127):
    try:
        with open(f"{chr(i)}.txt", "w") as f:
            f.write("pog")
    except Exception as e:
        print(f"err for {i} ", e)
