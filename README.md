# 🎨 Bubble Sort Visualizer

**Beautiful real-time visualization of the Bubble Sort algorithm**

## ✨ Features

- 🌈 Dynamic Gradient Colors
- 📊 Real-time Statistics (Comparisons & Swaps)
- 🎬 Smooth Animations
- 🎯 Color-coded Comparisons
- ✅ Completion Indicator
- 🎨 Modern Dark Theme UI

## 🛠️ Requirements

- C++ Compiler (GCC 7+, Clang 5+, or MSVC 2017+)
- SFML 2.5+

## 📦 Installation

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

### macOS
```bash
brew install sfml
```

### Windows
Download SFML from [official website](https://www.sfml-dev.org/download.php)

## 🚀 Usage

### Clone
```bash
git clone https://github.com/haladayyeh/bubble-sort-visualizer.git
cd bubble-sort-visualizer
```

### Compile
```bash
g++ bubble_sort_visualizer.cpp -o visualizer -lsfml-graphics -lsfml-window -lsfml-system -std=c++11
```

### Run
```bash
./visualizer
```

## 🔧 Customization

Modify the data array:
```cpp
vector<int> data = {180, 90, 150, 50, 120, 40, 200, 70, 160, 100, 140, 80};
```

Adjust animation speed:
```cpp
sleep(milliseconds(50));  // Change 50 to your preferred speed
```

## 🎯 Algorithm Complexity

- **Time Complexity**: O(n²)
- **Space Complexity**: O(1)
- **Best Case**: O(n)
- **Worst Case**: O(n²)

## 🤝 Contributing

Contributions are welcome! Feel free to fork and submit pull requests.

## 📄 License

MIT License - feel free to use this project for learning and educational purposes.

## 🌟 Show Your Support

Give a ⭐️ if this project helped you!

---
## 👤 Author

**hala dayyeh**
- GitHub: [@haladayyeh](https://github.com/haladayyeh)

Made with ❤️ and C++
