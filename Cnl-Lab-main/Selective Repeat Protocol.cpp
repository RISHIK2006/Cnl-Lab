#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10

using namespace std;

bool transmitFrame(int frame) {
    int chance = rand() % 10;  
    return (chance >= 2);  
}

void selectiveRepeat() {
    int frames[TOTAL_FRAMES];
    vector<bool> ack(TOTAL_FRAMES, false);  
    for (int i = 0; i < TOTAL_FRAMES; i++) frames[i] = i;

    int send_base = 0;

    cout << "Starting Selective Repeat Protocol Simulation..." << endl;

    while (send_base < TOTAL_FRAMES) {
        for (int i = 0; i < WINDOW_SIZE && send_base + i < TOTAL_FRAMES; i++) {
            int frame_to_send = send_base + i;
            if (!ack[frame_to_send]) {
                cout << "Sending frame: " << frames[frame_to_send] << endl;
                if (transmitFrame(frames[frame_to_send])) {
                    cout << "Acknowledgment received for frame: " << frames[frame_to_send] << endl;
                    ack[frame_to_send] = true;
                } else {
                    cout << "Error in frame: " << frames[frame_to_send] << ". Will retransmit." << endl;
                }
            }
        }

        while (send_base < TOTAL_FRAMES && ack[send_base]) {
            send_base++;
        }
    }
    cout << "All frames sent successfully using Selective Repeat!" << endl;
}

int main() {
    srand(time(0));
    selectiveRepeat();
    return 0;
}
