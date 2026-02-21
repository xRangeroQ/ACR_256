# ACR_256 (Aes Cryptography 256) 🛡️

**ACR_256** is a lightweight and high-performance C++ utility designed for secure **AES-256-GCM** operations. It simplifies the encryption process by bundling data with essential metadata, delivering a secure and portable Base64-encoded output.

## ✨ Key Features
- **Algorithm:** AES-256-GCM.
- **Integrated Metadata**: Each package automatically includes temporal and integrity verification data.
- **Timestamping:** Includes an 8-byte Unix timestamp in every package for temporal verification.
- **Portable Output:** All results are provided in Base64 format for easy storage and transmission.
- **Zero Dependencies:** Optimized for static linking to ensure the executable runs standalone on Windows environments.

---

## 🚀 Usage

### 1. Encryption
Provide the plaintext content and a 32-byte Base64 key:
```bash
./ACR_256.exe --content "Hello World" --set-key "BASE64_32BYTE_KEY_HERE"
```

### 2. Decryption
Pass the Base64-encoded package string and the matching key:
```bash
./ACR_256.exe -d "ENCRYPTED_BASE64_STRING" --set-key "BASE64_32BYTE_KEY_HERE"
```

### 🛠 Compilation (Windows / MinGW)
For a standalone executable without external dependencies, use the following build command:
```bash
g++ main.cpp Source/*.cpp -o ACR_256.exe -lssl -lcrypto -static -static-libgcc -static-libstdc++
```
