//******************************************************************************
//* Copyright (c) Jon Newman (jpnewman at mit snail edu) 
//* All right reserved.
//* This file is part of the Simple Tracker project.
//* This is free software: you can redistribute it and/or modify
//* it under the terms of the GNU General Public License as published by
//* the Free Software Foundation, either version 3 of the License, or
//* (at your option) any later version.
//* This software is distributed in the hope that it will be useful,
//* but WITHOUT ANY WARRANTY; without even the implied warranty of
//* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//* GNU General Public License for more details.
//* You should have received a copy of the GNU General Public License
//* along with this source code.  If not, see <http://www.gnu.org/licenses/>.
//******************************************************************************

#ifndef SYNCSHAREDMEMORYOBJECT_H
#define	SYNCSHAREDMEMORYOBJECT_H

#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "Position.h"

namespace shmem {

    template <class T>
    class SyncSharedMemoryObject {
    public:

        SyncSharedMemoryObject(void) :
          mutex(1)
        , write_barrier(0)
        , read_barrier(0)
        , new_data_barrier(0)
        , number_of_clients(0)
        , client_read_count(0) { }

        boost::interprocess::interprocess_semaphore mutex;
        boost::interprocess::interprocess_semaphore write_barrier;
        boost::interprocess::interprocess_semaphore read_barrier;
        boost::interprocess::interprocess_semaphore new_data_barrier;
        
        size_t number_of_clients;
        size_t client_read_count;

        void set_value(T value) {
            object = value;
        }

        T get_value(void) {
            return object;
        }

    private:
        T object;

    };
}

// Explicit instantiations
template class shmem::SyncSharedMemoryObject<shmem::Position>;


#endif	/* SYNCSHAREDMEMORYOBJECT_H */

