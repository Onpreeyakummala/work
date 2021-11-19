#pragma once
#include "Player.hpp"
#include"Enamy.hpp"
#include"Item.hpp"

class Game {

private:
   
    RenderWindow* window;
    Player* player;
    vector<Enamy>Enamys;
    Texture EnemyTexture;
    Texture EnemyTexture2;
    Texture EnemyTexture3;
    Texture lifeTexture;
    Sprite lifeSprite[3];
    Texture bgTexture;
    Sprite bgSprite;
    vector<Item>items;
    Sprite Itemsprite;
    Texture ItemTexture;
    float spTime;
    float spTimeMax;
    float immuneTime;
    float immuneTimeMax;
    int kill;
    int score; //§–·ππ
    int spawnItemDelay;
    bool isimmune;


public:

    Game() 
    {

        this->window = new RenderWindow(VideoMode(w, h), "My Game", Style::Fullscreen);
        this->window->setFramerateLimit(60);
        this->bgTexture.loadFromFile("Texture/bggcc.png");
        this->bgSprite.setTexture(bgTexture);
        this->bgSprite.setScale(Vector2f(0.95f, 0.8f)); 
        this->player = new Player(this->window);
        this->spTimeMax = 120.f;
        this->spTime = 0;
        this->EnemyTexture.loadFromFile("Texture/Enemy/11.png");
        this->EnemyTexture2.loadFromFile("Texture/Enemy/12.png");
        this->EnemyTexture3.loadFromFile("Texture/Enemy/13.png");
        this->lifeTexture.loadFromFile("Texture/heart.png");
        for (size_t i = 0; i < 3; i++)
        {
            lifeSprite[i].setTexture(lifeTexture);
           
        }
        this->immuneTimeMax = 120.f;
        this->immuneTime = immuneTimeMax;
        this->isimmune = 0;
        this->kill = 0; 

     

    }

    ~Game() 
    {
        delete this->window;
        delete this->player;
    }

    bool isRunning() 
    {

        return this->window->isOpen();
    }

    void processEvent() 
    {

        Event event;
        while (this->window->pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed)
                this->window->close();
            if (event.type == Event::TextEntered)
                cout << char(event.text.unicode) << endl;
            if (event.type == Event::KeyPressed)
            {
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    this->window->close();
                }
            }

        }
    }
   
    void update() 
    {

        if (spawnItemDelay <= 0)
        {
            //Item Items();
            int itemrandom = (rand() % 1920, rand() % 1080);
            this->items.push_back(Item(itemrandom, itemrandom,&this->ItemTexture)); 

            //if (itemrandom < 3) this->items.push_back(Item(this->randomIntRange(150, this->window->getSize().x - 200), -200.f, &this->ItemTexture, ITEM_HEAL));

            spawnItemDelay = 1200; //20«‘  ÿË¡‰Õ‡∑¡
        }
        else
        {
            spawnItemDelay--;
        }
        //§«“¡‡√Á«°“√‡°‘¥Enemy
        if (1 < kill <= 15 )
        {
            spTimeMax = 120 - (kill / 5) * 5; 
        }
        if (20 < kill <= 25)
        {
            spTimeMax = 120 - (kill / 5) * 10;
        }
        if (40 < kill <= 45)
        {
            spTimeMax = 120 - (kill / 5) * 8;
        }
        else
        {
            spTimeMax = 120 ;
        }
        // ÿË¡Enamy
        if (spTime>=spTimeMax)
        {
            int EnamyType =  rand() %3;
            if (EnamyType == 0)
            {
                Enamys.push_back(Enamy(&EnemyTexture,10,0.4));
            }
            if (EnamyType == 1)
            {
                Enamys.push_back(Enamy(&EnemyTexture2, 10,0.4));
            }
            if (EnamyType == 2)
            {
                Enamys.push_back(Enamy(&EnemyTexture3, 10,0.5));
            }
            spTime = 0;
        }
        else
        {
            spTime++;
        }
        //player
        this->player->updatePlayer();
        if (this->player->getHp() <= 0)
        {
            this->player->deletelife();
            this->player->setHpMax();
            this->isimmune = 1;
            this->immuneTime = 0;
        }
        if (isimmune ==1) //Õ¡µ–
        {
            immuneTime++;
        }
        if (immuneTime >= immuneTimeMax)
        {
            isimmune = 0;
        }
        for (size_t i = 0; i < this->player->getlife(); i++)
        {
            lifeSprite[i].setPosition(100+(i*125),50); //ª√—∫À—«„®
            lifeSprite[i].setScale(0.4f, 0.4f);
        }
        for (size_t i = 0; i < Enamys.size(); i++)
        {
            Enamys[i].update(player->getPosition());
            if (Enamys[i].getGlobalBounds().intersects(this->player->getGlobalBounds()))
            {
                if (isimmune == 0)
                {
                  this->player->getDamage(-10);
                }
                Enamys.erase(Enamys.begin()+i);
       
                break;
            }
            if (Enamys[i].getHp() <= 0)
            {
                Enamys.erase(this->Enamys.begin() + i);
                kill++;
                break;
            }
        }
        for (size_t i = 0; i < player->getBullet().size(); i++)
        {
            player->getBullet()[i].updateBullet();
            for (size_t j = 0; j <Enamys.size(); j++)
            {
                if (player->getBullet()[i].getGlobalBounds().intersects(Enamys[j].getGlobalBounds()))
                {
                    Enamys[j].updatehp(-5);
                    player->getBullet().erase(player->getBullet().begin() + i);
                
                    break;
                }
            }
        }

        for  (int i=0; i< items.size(); i++)
        {
            items[i].update();

        }
    
        
    }

    void clearScreen() 
    {

        this->window->clear();
    }

    void drawScreen() 
    {
        this->window->draw(this->bgSprite);
        this->player->draw();
        for (size_t i = 0; i < this->player->getlife(); i++)
        {
            this->window->draw(lifeSprite[i]);
        }
        for (size_t i = 0; i < Enamys.size(); i++)
        {
            Enamys[i].draw(*this->window);
        }

        for (int i = 0; i < items.size(); i++)
        {
            items[i].draw(this->window);

        }


       
    }

    void displayScreen() 
    {
        this->window->display();
     
    }

};
