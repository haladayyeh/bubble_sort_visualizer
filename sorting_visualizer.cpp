#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace sf;
using namespace std;

class SortVisualizer {
private:
    RenderWindow window;
    vector<int> arr;
    int windowWidth;
    int windowHeight;
    int barWidth;
    int spacing;
    int comparisons;
    int swaps;
    bool isSorting;
    bool isSorted;
    Font font;

    Color getGradientColor(int value, int maxValue) {
        float ratio = static_cast<float>(value) / maxValue;
        int r = static_cast<int>(255 * (1 - ratio));
        int g = static_cast<int>(255 * ratio * 0.7);
        int b = static_cast<int>(180 * ratio);
        return Color(r, g, b);
    }

    Color getComparisonColor(int index, int compareIndex, int maxIndex) {
        if (index == compareIndex) return Color(255, 50, 50);
        if (index == compareIndex + 1) return Color(255, 150, 50);
        if (index >= maxIndex) return Color(100, 100, 100);
        return Color(50, 200, 255);
    }

    void drawArray(int currentIndex = -1, int compareIndex = -1) {
        window.clear(Color(15, 15, 25));

        int maxVal = *max_element(arr.begin(), arr.end());
        
        for (size_t i = 0; i < arr.size(); ++i) {
            float barHeight = (arr[i] / static_cast<float>(maxVal)) * (windowHeight - 120);
            
            RectangleShape bar(Vector2f(barWidth, barHeight));
            bar.setPosition(i * (barWidth + spacing) + spacing, windowHeight - barHeight - 40);
            
            if (isSorted) {
                bar.setFillColor(Color(50, 255, 150));
                
                RectangleShape glow(Vector2f(barWidth + 4, barHeight + 4));
                glow.setPosition(i * (barWidth + spacing) + spacing - 2, windowHeight - barHeight - 42);
                glow.setFillColor(Color(50, 255, 150, 80));
                window.draw(glow);
            } else if (currentIndex != -1) {
                bar.setFillColor(getComparisonColor(i, compareIndex, currentIndex));
            } else {
                bar.setFillColor(getGradientColor(arr[i], maxVal));
            }
            
            RectangleShape outline(Vector2f(barWidth, barHeight));
            outline.setPosition(i * (barWidth + spacing) + spacing, windowHeight - barHeight - 40);
            outline.setFillColor(Color::Transparent);
            outline.setOutlineThickness(1);
            outline.setOutlineColor(Color(255, 255, 255, 30));
            
            window.draw(bar);
            window.draw(outline);

            if (font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") || 
                font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                Text text(to_string(arr[i]), font, 13);
                text.setPosition(i * (barWidth + spacing) + spacing + barWidth/2 - 8, 
                                windowHeight - 28);
                text.setFillColor(Color(220, 220, 220));
                window.draw(text);
            }
        }

        drawStats();
        window.display();
    }

    void drawStats() {
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") && 
            !font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
            return;
        }

        Text title("~ BUBBLE SORT ~", font, 30);
        title.setPosition(windowWidth/2 - 130, 18);
        title.setFillColor(Color(255, 200, 100));
        title.setStyle(Text::Bold);
        window.draw(title);

        stringstream ss;
        ss << "Comparisons: " << comparisons << "   Swaps: " << swaps;
        Text stats(ss.str(), font, 16);
        stats.setPosition(windowWidth/2 - 140, 58);
        stats.setFillColor(Color(180, 220, 255));
        window.draw(stats);

        if (isSorted) {
            Text completed("★ SORTED! ★", font, 36);
            completed.setPosition(windowWidth/2 - 95, windowHeight/2 - 55);
            completed.setFillColor(Color(100, 255, 180));
            completed.setStyle(Text::Bold);
            window.draw(completed);
        }
        
        Text footer("Press ESC to close", font, 12);
        footer.setPosition(windowWidth - 140, windowHeight - 25);
        footer.setFillColor(Color(150, 150, 150));
        window.draw(footer);
    }

public:
    SortVisualizer(const vector<int>& data, int width = 900, int height = 650) 
        : arr(data), windowWidth(width), windowHeight(height), 
          comparisons(0), swaps(0), isSorting(false), isSorted(false) {
        
        barWidth = (windowWidth - (arr.size() + 1) * 5) / arr.size();
        spacing = 5;
        
        window.create(VideoMode(windowWidth, windowHeight), 
                     "Bubble Sort - Visual Magic", 
                     Style::Close);
        window.setFramerateLimit(60);
    }

    void bubbleSort() {
        int n = arr.size();
        isSorting = true;
        
        for (int i = 0; i < n - 1; ++i) {
            bool swapped = false;
            
            for (int j = 0; j < n - i - 1; ++j) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed || 
                        (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
                        window.close();
                        return;
                    }
                }

                comparisons++;
                drawArray(n - i - 1, j);
                sleep(milliseconds(45));

                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swaps++;
                    swapped = true;
                    
                    drawArray(n - i - 1, j);
                    sleep(milliseconds(45));
                }
            }
            
            if (!swapped) break;
        }
        
        isSorting = false;
        isSorted = true;
        drawArray();
    }

    void run() {
        drawArray();
        sleep(milliseconds(800));
        
        bubbleSort();
        
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed || 
                    (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
                    window.close();
                }
            }
        }
    }
};

int main() {
    vector<int> data = {185, 95, 155, 48, 118, 42, 198, 72, 165, 102, 138, 85};
    
    SortVisualizer visualizer(data);
    visualizer.run();
    
    return 0;
}
