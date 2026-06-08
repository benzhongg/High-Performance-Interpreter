#pragma once

class FileReader
{
private:
    bool m_isReading { false };
public:
    FileReader();
    void run(/*Input File*/);
    void stop();
    bool isReading();
};