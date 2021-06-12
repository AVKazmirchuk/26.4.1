#pragma once

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <ctime>
#include <iomanip>
#include <optional>

using optTuple = std::optional<std::tuple<std::string, std::tm, std::tm>>;

class Track
{
private:

    //Поля: название, дата записи, продолжительность

    std::vector<std::tuple<std::string, std::tm, std::tm>> tracks;

public:

    void input(std::string&& title, std::tm& date, std::tm& duration);

    void output();

    const int getNumberOfRecords();

    const optTuple getRecordByTitle(std::string& title);

    const std::tuple<std::string, std::tm, std::tm>& getRecordByIDX(int idx);
};

class Player
{
private:

    Track* track = new Track;

    std::tuple<std::string, std::tm, std::tm> currentRecord;

    bool isPlay = false;
    bool isPause = false;

    void outputRecord(std::tuple<std::string, std::tm, std::tm>& currentRecord);

    void play();

    void pause();

    void next();

    void stop();

    void exit();

public:

    void fillTracks();

    void control();
};