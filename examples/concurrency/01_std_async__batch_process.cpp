#include "headers.h"

#include <future>
#include <mutex>
#include <chrono>
#include <queue>

class Batcher
{
public:
  Batcher()
    : taskDelay( 4 ),
      startTime( std::chrono::steady_clock::now() ) // only used for debugging
  {
  }

  void queue( const std::string& value )
  {
        std::unique_lock< std::mutex > lock( mutex );
        std::cout << "queuing '" << value << " at "
            << std::chrono::duration_cast< std::chrono::milliseconds >( 
                std::chrono::steady_clock::now() - startTime ).count() << "ms\n";
        work.push( value );
        // increase the time to process the queue to "now + 4 seconds"
        timeout = std::chrono::steady_clock::now() + taskDelay;
        if ( !running )
        {
            // launch a new asynchronous task which will process the queue
            task = std::async( std::launch::async, [this]{ processWork(); } );
            running = true;
        }
  }

  ~Batcher()
  {
        std::unique_lock< std::mutex > lock( mutex );
        // stop processing the queue
        closing = true;
        bool wasRunning = running;
        condition.notify_all();
        lock.unlock();
        if ( wasRunning )
        {
            // wait for the async task to complete
            task.wait();
        }
  }

private:
    std::mutex mutex;
    std::condition_variable condition;
    std::chrono::seconds taskDelay;
    std::chrono::steady_clock::time_point timeout;
    std::queue< std::string > work;
    std::future< void > task;
    bool closing = false;
    bool running = false;
    std::chrono::steady_clock::time_point startTime;

    void processWork()
    {
        std::unique_lock< std::mutex > lock( mutex );
        // loop until std::chrono::steady_clock::now() > timeout
        auto wait = timeout - std::chrono::steady_clock::now();
        while ( !closing && wait > std::chrono::seconds( 0 ) )
        {
            condition.wait_for( lock, wait );
            wait = timeout - std::chrono::steady_clock::now();
        }
        if ( !closing )
        {
            std::cout << "processing queue at " 
                << std::chrono::duration_cast< std::chrono::milliseconds >( 
                        std::chrono::steady_clock::now() - startTime ).count() << "ms\n";
            while ( !work.empty() )
            {
                std::cout << work.front() << "\n";
                work.pop();
            }
            std::cout << std::flush;
        }
        else
        {
            std::cout << "aborting queue processing at " 
            << std::chrono::duration_cast< std::chrono::milliseconds >( 
                std::chrono::steady_clock::now() - startTime ).count() 
            << "ms with " << work.size() << " remaining items\n";
        }
        running = false;
    }
};

int main()
{
    Batcher batcher;
    batcher.queue( "test 1" );
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    batcher.queue( "test 2" );
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    batcher.queue( "test 3" );
    std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
    batcher.queue( "test 4" );
    std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
    batcher.queue( "test 5" );
}