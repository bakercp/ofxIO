class AbstractDataView
{
public:
    AbstractDataView()
    {
    }

    virtual ~AbstractDataView()
    {
    }

    virtual std::size_t write(uint8_t data) = 0;
    virtual std::size_t write(uint16_t data) = 0;
    virtual std::size_t write(uint32_t data) = 0;
    virtual std::size_t write(uint64_t data) = 0;

    virtual std::size_t write(int8_t data) = 0;
    virtual std::size_t write(int16_t data) = 0;
    virtual std::size_t write(int32_t data) = 0;
    virtual std::size_t write(int64_t data) = 0;

    virtual std::size_t write(const uint8_t* data, std::size_t size) = 0;
    virtual std::size_t write(const uint16_t* data, std::size_t size) = 0;
    virtual std::size_t write(const uint32_t* data, std::size_t size) = 0;
    virtual std::size_t write(const uint64_t* data, std::size_t size) = 0;

    virtual std::size_t write(const int8_t* data, std::size_t size) = 0;
    virtual std::size_t write(const int16_t* data, std::size_t size) = 0;
    virtual std::size_t write(const int32_t* data, std::size_t size) = 0;
    virtual std::size_t write(const int64_t* data, std::size_t size) = 0;

    bool readUInt8(uint8_t& value) const = 0;
    bool readUInt16(uint16_t& value) const = 0;
    bool readUInt32(uint32_t& value) const = 0;
    bool readUInt64(uint64_t& value) const = 0;

    bool readInt8(int8_t& value) const = 0;
    bool readInt16(int16_t& value) const = 0;
    bool readInt32(int32_t& value) const = 0;
    bool readInt64(int64_t& value) const = 0;

    bool readUInt8(uint8_t* destination, std::size_t size) const = 0;
    bool readUInt16(uint16_t* destination, std::size_t size) const = 0;
    bool readUInt32(uint32_t* destination, std::size_t size) const = 0;
    bool readUInt64(uint64_t* destination, std::size_t size) const = 0;

    bool readInt8(int8_t* destination, std::size_t size) const = 0;
    bool readInt16(int16_t* destination, std::size_t size) const = 0;
    bool readInt32(int32_t* destination, std::size_t size) const = 0;
    bool readInt64(int64_t* destination, std::size_t size) const = 0;

};
