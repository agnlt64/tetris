#include <random>

#include "include/game.h"

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    timer = 0.0f;
    muted = false;
    InitAudioDevice();
    music = LoadMusicStream("assets/sounds/music.mp3");
    PlayMusicStream(music);
}

Game::~Game()
{
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, blocks.size() - 1);

    int randomIndex = dist(rng);
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);
        break;
    }
}

void Game::HandleInput()
{
    constexpr float interval = 0.1f;
    if (gameOver && GetKeyPressed() != 0)
    {
        gameOver = false;
        Reset();
    }

    if (IsKeyDown(KEY_LEFT))
    {
        timer += GetFrameTime();
        if (timer >= interval)
        {
            MoveBlockLeft();
            timer = 0.0f;
        }
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        timer += GetFrameTime();
        if (timer >= interval)
        {
            MoveBlockRight();
            timer = 0.0f;
        }
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        timer += GetFrameTime();
        if (timer >= interval * 0.5)
        {
            MoveBlockDown();
            timer = 0.0f;
        }
        // UpdateScore(0, 1);
    }
    else if (IsKeyPressed(KEY_UP))
    {
        RotateBlock();
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
        DockBlock();
    }
    else if (IsKeyPressed(KEY_SEMICOLON) || IsKeyPressed(KEY_M)) // ; on qwerty is m on azerty
    {
        muted = !muted;
    }

    if (!muted) ResumeMusicStream(music);
    else PauseMusicStream(music);
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

void Game::DockBlock()
{
    while (BlockFits())
    {
        currentBlock.Move(1, 0);
    }
    currentBlock.Move(-1, 0);
    LockBlock();
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotation();
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        UpdateScore(rowsCleared);
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

// https://tetris.wiki/Scoring, Original BPS Scoring System
void Game::UpdateScore(int linesCleared)
{
    switch (linesCleared)
    {
    case 1:
        score += 40;
        break;
    case 2:
        score += 100;
        break;
    case 3:
        score += 300;
        break;
    case 4:
        score += 1200;
        break;
    default:
        break;
    }
}
