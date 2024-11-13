#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10

using namespace std;

bool transmitFrame(int frame)
{
    int chance = rand() % 10;
    return (chance >= 2);
}

void goBackN()
{
    int frames[TOTAL_FRAMES];
    for (int i = 0; i < TOTAL_FRAMES; i++)
        frames[i] = i;

    int send_base = 0;
    int next_frame_to_send = 0;

    cout << "Starting Go-Back-N Protocol Simulation..." << endl;

    while (send_base < TOTAL_FRAMES)
    {

        while (next_frame_to_send < send_base + WINDOW_SIZE && next_frame_to_send < TOTAL_FRAMES)
        {
            cout << "Sending frame: " << frames[next_frame_to_send] << endl;
            next_frame_to_send++;
        }

        for (int i = send_base; i < next_frame_to_send; i++)
        {
            if (transmitFrame(frames[i]))
            {
                cout << "Acknowledgment received for frame: " << frames[i] << endl;
                send_base++;
            }
            else
            {
                cout << "Error in frame: " << frames[i] << ". Retransmitting from frame: " << frames[send_base] << endl;
                next_frame_to_send = send_base;
                break;
            }
        }
    }

    cout << "All frames sent successfully using Go-Back-N!" << endl;
}

int main()
{
    srand(time(0));
    goBackN();
    return 0;
}
