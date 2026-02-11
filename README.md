<p align="center">
  <b>FOCUS!  → ✷ ←  FOCUS!</b><br>
</p>

# TetOS

**TetOS** is a hobby operating system that is currently under development (very early stage), built with lots of love! ♡

## Why "TetOS"?

**TetOS** name references an UTAU (a voice synthesis program) named **Kasane Teto** (重音テト) but the actual name comes from **Machine Love** by Jamie Paige (feat. Kasane Teto) songs video, a detail [at start of the video](https://youtu.be/sqK-jh4TDXo?si=N67gZI-8tJyRWdVY&t=4) that when a computer boots, its shows **TetOS** (maybe the name is has deeper connections than I think, but I see it from here). I selected this name, because I love Teto. What did you expect?

## Motivation of this project

When I first started learning C, it was honestly awful, really awful. I wanted to build my own operating system, but I had no understanding of low-level programming, in fact, I had almost no knowledge or experience in programming at all. I got stuck on basic data types and eventually gave up. But now! I have enough knowledge to start (I think) and I have my love for Teto on my side too. So, I can start the journey that wants so much patience and I can fulfill my dreams that I try to catch for years. So I can put down my head on my pillow with no regrets!

## Detailed Roadmap

- [x] Basic bootloader setup and kernel loading
- [x] Kernel entry point and basic initialization
- [x] Drawing pixels on screen with framebuffer
- [ ] GDT and IDT setup for handling interrupts
- [ ] Implementing basic memory management (paging, heap)
- [ ] Basic keyboard input handling
- [ ] Implementing a simple shell for user interaction
- [ ] Adding support for file systems and probably making a new one!

### What comes in future?

Future you ask? Heh, I'm not a human that can see the future but at least I'm a human that can have ideas.

- [x] The first thing is... a bootable kernel
- [ ] And then making the OS interactable with user
- [ ] Making a desktop environment for OS
- [ ] Adding internet connection too!

*And these are just temporary dreams that will come true eventually(?), but for now, I leaving these ideas for my future self. >:)*

## Current Status

🟡 **Early Stage** - architecture planning, thinking about new features that will be added in the future, bootloader experiments.
*(And reading theories about computers, duh!)*

The system is bootable and currently shows only a red screen... but no worries! Maybe its not usable right now, but it will someday hopefully.

## Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/vortique/TetOS
   cd TetOS
   make # or make run to build and run with QEMU
   ```

### Build Requirements

- GCC (or LLVM/Clang)
- NASM (for assembly)
- make (for build automation)
- QEMU (for testing the OS in a virtual environment)
- xorriso (for creating bootable ISO images)

## Tech Stack

- **Programming Languages**: C and Assembly (so fun, yeah...)
- **Architecture**: Targeting x86_64 for now
- **Bootloader**: [Limine](https://codeberg.org/Limine/Limine)

## License

I want to spread Teto everywhere possible in the internet, so you can spread our Teto love under [the MIT license](LICENSE)!

<details>
<summary>Is this OS approved from big leagues?</summary>
  
**Yeah! Teto approves this OS.**
  
> TETOTETOTETO~ ♡
> 
*- Kasane Teto*

</details>
