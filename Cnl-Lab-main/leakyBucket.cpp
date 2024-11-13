#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

void leakyBucket(int bucketSize, int outputRate, vector<int> packetSizes) {
    queue<int> bucket;
    int currentBucketSize = 0;

    cout << "Starting Leaky Bucket Simulation..." << endl;

    for (size_t i = 0; i < packetSizes.size(); i++) {
        int packetSize = packetSizes[i];
        
        cout << "Packet " << i + 1 << " of size " << packetSize << " arrives." << endl;
        
        if (currentBucketSize + packetSize > bucketSize) {
            cout << "Bucket overflow! Packet " << i + 1 << " is discarded." << endl;
        } else {
            bucket.push(packetSize);
            currentBucketSize += packetSize;
            cout << "Packet " << i + 1 << " added to the bucket. Current bucket size: " 
                 << currentBucketSize << "/" << bucketSize << endl;
        }

        while (!bucket.empty()) {
            int packet = bucket.front();
            if (packet <= outputRate) {
                cout << "Transmitting packet of size " << packet << endl;
                bucket.pop();
                currentBucketSize -= packet;
            } else {
                cout << "Transmitting part of packet, output rate: " << outputRate << endl;
                bucket.front() -= outputRate;
                currentBucketSize -= outputRate;
            }
            
            cout << "Current bucket size after transmission: " 
                 << currentBucketSize << "/" << bucketSize << endl;

            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    cout << "All packets processed in the leaky bucket!" << endl;
}

int main() {
    int bucketSize, outputRate;
    vector<int> packetSizes;
    int numPackets = 5;

    cout << "Enter the bucket size: ";
    cin >> bucketSize;

    cout << "Enter the output rate: ";
    cin >> outputRate;

    cout << "Enter the sizes of up to " << numPackets << " packets:" << endl;
    for (int i = 0; i < numPackets; i++) {
        int packetSize;
        cout << "Packet " << i + 1 << " size: ";
        cin >> packetSize;
        packetSizes.push_back(packetSize);
    }

    leakyBucket(bucketSize, outputRate, packetSizes);

    return 0;
}
