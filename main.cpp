/*
 * Blink for Raspberry Pi Pico
 *
 * @version     1.0.0
 * @author     Justin Berkshire
 * @copyright   2022
 * @licence     MIT
 *
 */
#include "main.h"
using namespace std;

class i2c_node {
    private: int address;
    private: int freq = 100000;
           i2c_node(uint sda, uint scl) {
               //init pins
               gpio_init(sda);
               gpio_init(scl);
               gpio_set_function(sda, GPIO_FUNC_I2C);
               gpio_set_function(scl, GPIO_FUNC_I2C);
               gpio_pull_up(sda);
               gpio_pull_up(scl);
               //set up i2c connect
               i2c_init(i2c1, freq);
               address = findAvailableAddress();
               i2c_set_slave_mode(i2c1, true, address);
           }
    public: int getAddress() {
        return address;
    };
    // public: int readCommanderMessage() {
        
    //     uint messageLength = i2c_get_read_available(i2c1);

    //     uint8_t fullMessage[messageLength];

    //     i2c_read_raw_blocking (i2c1, fullMessage, messageLength);

    //     return *fullMessage;

    // }
    private: bool reserved_addr(uint8_t addr) {
        return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
    };
    private: int findAvailableAddress() {

        for (int addr = 0; addr < (1 << 7); ++addr) {
            if (addr % 16 == 0) {
                printf("%02x ", addr);
            }

            int ret;
            uint8_t rxdata;
            if (reserved_addr(addr))
                ret = PICO_ERROR_GENERIC;
            else
                ret = i2c_read_blocking(i2c0, addr, &rxdata, 1, false);

            if (ret < 0) {
                return addr;
            }
        }

        sleep_ms(2000);
    }
};

int main() {
    const uint LED = PICO_DEFAULT_LED_PIN;

    gpio_init(LED);

    gpio_set_dir(LED, GPIO_OUT);

    stdio_init_all();

    int a = 4;

    int b = 8;

    int c = a + b;

    cout << c << '\n';

    while (true) {
        cout << "Deadly Virus";
        gpio_put(LED, 1);
        sleep_ms(a * 100);
        gpio_put(LED, 0);
        sleep_ms(b * 100);
    }

    return 0;
}
