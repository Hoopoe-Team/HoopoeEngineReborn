#include <iostream>
#include <memory>
#include <Hoopoe/application.hpp>

class MyApp : public HoopoeEngine::Application
{
    private:
        int frame = 0;
    public:
        virtual void on_update() override
        {
            //std::cout << "Update frame: " << frame++ << std::endl; 
        }

};

int main()
{
    auto myApp = std::make_unique<MyApp>();
    
    int returnCode = myApp->start(1024,512,"Test");

    return returnCode;
}