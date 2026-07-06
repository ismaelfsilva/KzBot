# KzBot

Legacy C++/Qt6 project for OT (Open Tibia) 12 client automation — **does not work on the official Tibia client (CipSoft)**, only on OT servers using protocol 12.

This repository is published as an archived, unfinished historical/educational artifact. It is not maintained, not supported, and not intended for use against live games or services.

## Context

KzBot was my first large C++ project and my first real contact with Qt. It started as an automation client for Tibia 12 OT servers, reading process memory to reconstruct game state and simulating input (keyboard, mouse, window messages).

The bot was commercialized and served approximately 700 users during its active period, with a custom license server for authentication, version-gated updates, and multi-OT support.

Most of the code was written in 2022-2023, when I was learning C++ by doing — this shows in many questionable design choices, mixed paradigms, and code smells that I would identify and avoid today.

The value of this repository today:

- Honest record of my progression with C++, Qt, OpenSSL, and WinAPI.
- Practical example of desktop automation, process memory reading, input simulation, remote API integration, and a homemade licensing system.
- Case study on what **not** to do in authentication security and memory management.

## Repository Status

- Commits the latest local working version I had, including uncommitted improvements (PvP tools, new client version support, performance tweaks).
- **Branch**: `master` (single).
- **Remote**: `github.com/ismaelfsilva/KzBot`.
- **License**: MIT.

## What It Does

KzBot attaches to a running Tibia 12 OT client process, reads process memory to reconstruct game state (player, creatures, battlelist, map, inventory, cooldowns, hotkeys), and executes automated actions:

- **Remote authentication**: HTTPS login with HMAC-SHA256 challenge-response.
- **Cavebot**: automated walking, looting, targeting, spell/item use.
- **Healer**: auto healing by HP/MP, mana shield, spells.
- **Party Hunt**: group hunt automation.
- **PvP Tools**: player-vs-player utilities.
- **Tools**: anti-idle, auto food, auto buff, hold position.
- **Keybinding**: Tibia hotkey simulation via WinAPI.
- **Updater**: periodic re-authentication and license verification.

## Stack

- **Language**: C++17
- **Framework**: Qt 6.5.1 (Widgets, Core, Network)
- **Build**: CMake 3.5+, MSVC 2019 64-bit
- **Cryptography**: OpenSSL (EVP, SHA256, HMAC, RSA)
- **Windows API**: WinAPI (processes, windows, input, registry)
- **Networking**: QNetworkAccessManager (HTTPS)

## Architecture

- `Addresses/`: version-specific memory offsets and structures.
- `Objects/`: C++ wrappers for in-memory game objects (player, creature, battlelist, chat, inventory, cooldowns, etc.).
- `Threads/`: parallel execution loops (healer, partyhunt, pvptools, tools, updater).
- `UI/`: Qt Designer interface (login, main, config, healer, cavebot, pvp, partyhunt).
- `Settings/`: configuration, action rules, target rules, combo rules, global state.
- `Util/`: helpers (WinAPI, input, enums, API manager).
- `apimanager.cpp`: abandoned RSA authentication attempt (not compiled, non-functional).

## Known Flaws and Improvements

These notes are intentional. This was my first large C++ and Qt project, and the points below document what I would do differently today.

### Security

| Flaw in the old version | Location | What should be improved |
| --- | --- | --- |
| 10 symmetric HMAC keys hardcoded in source | `UI/loginwindow.cpp:120-131`, `Threads/updater.cpp:98-109` | Use asymmetric keys (RSA/Ed25519) with embedded public key and server-side private key. Or standard JWT signing. |
| Password sent as plaintext in POST body | `loginwindow.cpp:71-72` | Use challenge-response (SRP, PAKE) or at least client-side hashing. |
| "Remember Me" saves password in Windows Registry in plaintext | `loginwindow.cpp:155-158` | Use Windows Credential Manager or store a session token instead of the password. |
| Entire auth protocol exposed in source code | Both files | Use a standard protocol (OAuth2, JWT) instead of a homemade scheme with no nonce, salt, or key rotation. |
| No SSL certificate validation or pinning | `loginwindow.cpp:76-81` | Add certificate validation and HPKP or CA pinning. |

### Architecture and Engineering

| Flaw in the old version | What should be improved |
| --- | --- |
| **Critical memory leak**: `Threads/updater.cpp:188-210` allocates new `Healer`, `Tools`, `PvPTools`, `PartyHunt` objects with `new` on every main loop iteration (~10ms) without ever deleting them. Each object holds a `std::thread` that runs once and finishes, but the heap memory and thread handle are never freed. Memory grows unbounded and the bot starts stuttering after minutes. | Create objects once at startup, keep them as members of `Updater`, or use free functions without heap allocation. |
| Static global state (`Globals` entirely static class with dozens of mutable fields) | Split into services with clear lifecycle, dependency injection, and encapsulation. |
| Threads managed manually with `std::thread::detach()` and raw `bool` flags | Use `QThread` with event loops, signals/slots for communication, `QSharedPointer`/`QAtomicInt` for control. |
| Broad `catch (...)` blocks wrapping large `try` sections | Use specific exception types, structured logging, and per-operation fallback. |
| WinAPI, Qt, OpenSSL, and domain logic all mixed in the same files | Separate into layers: process access, domain model, action executor, UI. |
| Global input queue shared across threads with no explicit mutex | Use `QMutex`/`QReadWriteLock` or lock-free queues with `QAtomic` and signals. |
| Hardcoded absolute Qt path in CMake (`C:/Qt/6.5.1/msvc2019_64`) | Use `find_package` with version ranges, or manage dependencies via vcpkg/conan. |
| XML config files (`default.xml`, `hunt.xml`, `Data/spells.xml`) not included in repository | Include sanitized examples with documented schemas. |
| Dead code kept: `apimanager.cpp` not compiled, references nonexistent `public_key.pem`, uses `your_license_key_here` placeholder | Remove dead code or explicitly document it as experimental/abandoned. |

### Client Compatibility

| Flaw in the old version | What should be improved |
| --- | --- |
| Hardcoded memory addresses per client version (`Addresses/Versions/`) | Isolate version profiles with pattern/signature validation before use. |
| Assumes the client is always on the same version and memory layout | Add struct integrity checks and safe fallback when the version changes. |
| Anti-debug calls commented out (never executed) | Either implement properly or remove — commented-out dead code is noise. |

### Testing and Build

| Flaw in the old version | What should be improved |
| --- | --- |
| No automated tests (unit, integration, or E2E) | Add tests for config parsing, input logic, signature validation, and action rules. |
| No CI/CD configured | Add GitHub Actions for build and basic linting. |
| Manual build dependent on original environment (Qt + OpenSSL + VS2019) | Containerize or document setup step by step with vcpkg. |
| Marketing assets in `../KzSoft/` outside the repository | Either move into the repo or add to `.gitignore`. |

## Security Note

This repository contains **hardcoded symmetric cryptographic keys** (10 HMAC-SHA256 keys) used to verify license server responses. These keys should be considered **public/compromised** from the moment the source code was made public. The server `tibia.kzsoft.com.br` is likely defunct, so the practical risk is zero, but the security flaw is real and documented here as an example of what **not** to do.

No real user passwords, API tokens, or infrastructure keys are present in the repository or its history.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
