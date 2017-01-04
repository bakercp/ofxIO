//
// Copyright (c) 2010 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofTypes.h"

//
//namespace ofx {
//namespace IO {
//
//template <class T>
//class ObjectPool
//{
//private:
//    struct External_Deleter {
//        explicit External_Deleter(std::weak_ptr<ObjectPool<T>* > pool)
//        : pool_(pool) {}
//
//        void operator()(T* ptr) {
//            if (auto pool_ptr = pool_.lock()) {
//                try {
//                    (*pool_ptr.get())->add(std::unique_ptr<T>{ptr});
//                    return;
//                } catch(...) {}
//            }
//            std::default_delete<T>{}(ptr);
//        }
//    private:
//        std::weak_ptr<ObjectPool<T>* > pool_;
//    };
//
//public:
//    using ptr_type = std::unique_ptr<T, External_Deleter >;
//
//    ObjectPool() : this_ptr_(new ObjectPool<T>*(this)) {}
//    virtual ~ObjectPool(){}
//
//    void add(std::unique_ptr<T> t) {
//        pool_.push(std::move(t));
//    }
//
//    
//    ptr_type acquire(uint64_t timeoutMilliseconds = 1000)
//    {
//        std::unique_lock<std::mutex> lock(_mutex);
//
//        if (!pool_.empty())
//        {
//            return _pop();
//        }
//
//        if (_size >= _peakCapacity)
//        {
//            if (timeoutMilliseconds == 0)
//            {
//                return nullptr;
//            }
//
//            while (_size >= _peakCapacity)
//            {
//                _availableCondition.wait_for(lock, std::chrono::milliseconds(timeoutMilliseconds));
//
//
////                if (!_availableCondition.tryWait(_mutex, timeoutMilliseconds))
////                {
//                    // timeout
//                    return nullptr;
////                }
//            }
//        }
//        else
//        {
//            // _size < _peakCapacity
//            return _create();
//        }
//
////        assert(!pool_.empty());
////        ptr_type tmp(pool_.top().release(),
////                     External_Deleter{std::weak_ptr<ObjectPool<T>*>{this_ptr_}});
////        pool_.pop();
////        return std::move(tmp);
//    }
//    
//    bool empty() const {
//        return pool_.empty();
//    }
//    
//    size_t size() const {
//        return pool_.size();
//    }
//
//protected:
//
//        /// \brief Subclasses must implement this method to create new objects.
//        virtual std::unique_ptr<T> create() = 0;
//
//private:
//    ptr_type _create()
//    {
//        _size++; // Increment when we create.
//        return ptr_type(create().release(), External_Deleter{std::weak_ptr<ObjectPool<T>*>{this_ptr_}});
//    }
//
//    ptr_type _pop()
//    {
//        _size++;
//        ptr_type tmp(pool_.top().release(), External_Deleter{std::weak_ptr<ObjectPool<T>*>{this_ptr_}});
//        pool_.pop();
//        return std::move(tmp);
//    }
//
//    void _push(std::unique_ptr<T> t)
//    {
//        _size--;
//        pool_.push(std::move(t));
//        _availableCondition.notify_one();
//    }
//
//        std::size_t _peakCapacity = 100;
//        std::size_t _size = 0;
//
//    std::condition_variable _availableCondition;
//
//    mutable std::mutex _mutex;
//
//    std::shared_ptr<ObjectPool<T>* > this_ptr_;
//    std::stack<std::unique_ptr<T> > pool_;
//};
//
//
////
/////// Based on https://stackoverflow.com/questions/27827923/c-object-pool-that-provides-items-as-smart-pointers-that-are-returned-to-pool
/////// and Poco::ObjectPool.
////template <class T>//, class FactoryType>
////class ObjectPool
////{
////private:
////    typedef ObjectPool<T>* ObjectPoolPtr;
////    typedef std::shared_ptr<ObjectPoolPtr> SharedObjectPoolPtr;
////    typedef std::weak_ptr<ObjectPoolPtr> WeakObjectPool;
////
////    struct ObjectPoolDeleter
////    {
////        explicit ObjectPoolDeleter(WeakObjectPool pool): _pool(pool)
////        {
////        }
////
////        void operator()(T* ptr)
////        {
////            auto pool_ptr = _pool.lock();
////
////            if (pool_ptr != nullptr)
////            {
////                try
////                {
////                    (*pool_ptr.get())->_push(std::unique_ptr<T>(ptr));
////                    return;
////                }
////                catch (...)
////                {
////                    // Catch a bad alloc.
////                }
////            }
////
////            std::default_delete<T>{}(ptr);
////        }
////    private:
////        WeakObjectPool _pool;
////        
////    };
////
////public:
////    typedef std::unique_ptr<T, ObjectPoolDeleter> PtrType;
////
////    ObjectPool(): _this_ptr(std::make_shared<ObjectPoolPtr>(this))
////    {
////    }
////
////    virtual ~ObjectPool()
////    {
////    }
////
////    PtrType acquire(uint64_t timeoutMilliseconds = 1000)
////    {
////        std::unique_lock<std::mutex> lock(_mutex);
////
////        if (!_pool.empty())
////        {
////            return _pop();
////        }
////
////        if (_size >= _peakCapacity)
////        {
////            if (timeoutMilliseconds == 0)
////            {
////                return nullptr;
////            }
////
////            while (_size >= _peakCapacity)
////            {
////                _availableCondition.wait_for(lock, std::chrono::milliseconds(timeoutMilliseconds));
////
////
//////                if (!_availableCondition.tryWait(_mutex, timeoutMilliseconds))
//////                {
////                    // timeout
////                    return nullptr;
//////                }
////            }
////        }
////        else
////        {
////            // _size < _peakCapacity
////            return _create();
////        }
////    }
////
////    std::size_t peakCapacity() const
////    {
////        std::unique_lock<std::mutex> lock(_mutex);
////        return _peakCapacity;
////    }
////
////    size_t inUse() const
////    {
////        std::unique_lock<std::mutex> lock(_mutex);
////        return _size;
////    }
////
////    size_t available() const
////    {
////        std::unique_lock<std::mutex> lock(_mutex);
////        return _pool.size();
////    }
////
////protected:
////
////    /// \brief Subclasses must implement this method to create new objects.
////    virtual std::unique_ptr<T> create() = 0;
////
////private:
////    PtrType _create()
////    {
////        _size++; // Increment when we create.
////        return PtrType(create().release(), ObjectPoolDeleter(WeakObjectPool(_this_ptr)));
////    }
////
////    PtrType _pop()
////    {
////        _size++;
////        PtrType tmp(_pool.top().release(), ObjectPoolDeleter(WeakObjectPool(_this_ptr)));
////        _pool.pop();
////        return std::move(tmp);
////    }
////
////    void _push(std::unique_ptr<T> t)
////    {
////        _size--;
////        _pool.push(std::move(t));
////        _availableCondition.notify_one();
////    }
////
////    std::condition_variable _availableCondition;
////
////    mutable std::mutex _mutex;
////
////    SharedObjectPoolPtr _this_ptr;
////
////    std::stack<std::unique_ptr<T>> _pool;
////
////
////};


} } // namespace ofx::IO
