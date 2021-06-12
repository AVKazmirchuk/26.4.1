#include <iostream>
#include "../include/header.h"

void Track::input(std::string&& title, std::tm& date, std::tm& duration)
{
    tracks.push_back({ title, date, duration });
}

void Track::output()
{
    std::cout << "\n\nTracks\n";
    std::cout << "------\n";

    for (const auto& [title, date, duration] : tracks)
    {
        std::cout << title << ' ' << std::put_time(&date, "%Y/%m/%d") <<
                  ' ' << std::put_time(&duration, "%S") << '\n';
    }
}

const int Track::getNumberOfRecords()
{
    return tracks.size();
}

const optTuple Track::getRecordByTitle(std::string& title)
{
    for (const auto& elem : tracks)

        if (title == std::get<0>(elem)) return { elem };

    return {};
}

const std::tuple<std::string, std::tm, std::tm>& Track::getRecordByIDX(int idx)
{
    return tracks[idx];
}

void Player::outputRecord(std::tuple<std::string, std::tm, std::tm>& currentRecord)
{
    std::cout << "Record \"" << std::get<0>(currentRecord) << ' ' <<
              std::put_time(&std::get<1>(currentRecord), "%Y/%m/%d") <<
              ' ' << std::put_time(&std::get<2>(currentRecord), "%S") << '\"';
}

void Player::play()
{
    if (isPause)
    {
        isPause = false;

        outputRecord(currentRecord);
        std::cout << " continues";
        return;
    }

    if (isPlay) return;
    else
    {
        std::string title;

        while (true)
        {
            std::cout << "Record title: ";
            std::getline(std::cin, title);

            optTuple tmp = track->getRecordByTitle(title);

            if (tmp)
            {
                isPlay = true;

                currentRecord = *tmp;

                outputRecord(currentRecord);
                std::cout << " is being played";
                return;
            }
            else
            {
                std::cout << "Record not found!\n";
                continue;
            }
        }
    }
}

void Player::pause()
{
    if (isPlay && !isPause)
    {
        isPause = true;

        outputRecord(currentRecord);
        std::cout << " on pause";
    }
}

void Player::next()
{
    if (!isPlay)
    {
        isPlay = true;

        int idx = rand() % (track->getNumberOfRecords());

        currentRecord = track->getRecordByIDX(idx);
        outputRecord(currentRecord);
        std::cout << " is being played";
    }
}

void Player::stop()
{
    if (isPlay)
    {
        isPlay = false;
        isPause = false;

        outputRecord(currentRecord);
        std::cout << " stopped";
    }
}

void Player::exit()
{
    delete track;
}

void Player::fillTracks()
{
    //Заполнение списка воспроизведения

    std::tm date, duration;
    const std::string title = "group";
    std::string tmp;

    for (int i = 1; i <= 9; ++i)
    {
        date.tm_year = 100 + i; date.tm_mon = i; date.tm_mday = i; duration.tm_sec = i * 6;

        track->input(title + std::to_string(i), date, duration);
    }
}

void Player::control()
{
    std::string command;

    while (true)
    {
        track->output();

        std::cout << "\nCommand: play, pause, next, stop, exit: ";

        std::getline(std::cin, command);

        if (command == "play") play();
        else if (command == "pause") pause();
        else if (command == "next") next();
        else if (command == "stop") stop();
        else if (command == "exit")
        {
            exit();
            return;
        }
        else std::cout << "Invalid command!\n";
    }
}