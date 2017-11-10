#pragma once

namespace m7 {

template <typename Alloc>
    class AllocatorDeleter {
        public:
            AllocatorDeleter() = default;
            explicit AllocatorDeleter(Alloc* alloc);

            template <typename T>
                void operator()(T* p) const;

        private:
            Alloc* _alloc = nullptr;
    };

} //namespace m7
