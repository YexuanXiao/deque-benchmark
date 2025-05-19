#include <cstddef>
#include <vector>
#include "benchmark/benchmark.h"
#include <deque>
#if defined(TEST_STD)
#include <deque>
#endif
#include "deque/deque.hpp"

template<typename T>
std::vector<T> make_vector(std::size_t length){
    std::vector<T> result;
    for(std::size_t i=0uz;i!=length;++i){
        result.push_back(i);
    }
    return result;
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void constructor_3(benchmark::State& state) {
    for (auto _ : state) {
        Deque<T,std::allocator<T>> d(Length);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void constructor_4(benchmark::State& state) {
    for (auto _ : state) {
        Deque<T,std::allocator<T>> d(Length, 0);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void constructor_5_raw_ptr(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        Deque<T,std::allocator<T>> d(vec.data(),vec.data()+Length);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void constructor_5_vec_it(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        Deque<T,std::allocator<T>> d(vec.begin(),vec.end());
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void constructor_6(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void constructor_7_copy(benchmark::State& state) {
    Deque<T,std::allocator<T>> t(Length,0);
    for (auto _ : state) {
        Deque<T,std::allocator<T>> d(t);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void at(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    Deque<T,std::allocator<T>> d(std::from_range,vec);
    for (auto _ : state) {
        for(std::size_t i=0uz;i!=Length;++i){
            auto r = d.at(i);
            benchmark::DoNotOptimize(r);
        }
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void operator_at(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    Deque<T,std::allocator<T>> d(std::from_range,vec);
    for (auto _ : state) {
        for(std::size_t i=0uz;i!=Length;++i){
            auto r = d[i];
            benchmark::DoNotOptimize(r);
        }
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void front(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    Deque<T,std::allocator<T>> d(std::from_range,vec);
    for (auto _ : state) {
        for(std::size_t i=0uz;i!=Length;++i){
            benchmark::DoNotOptimize(d.front());
        }
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void back(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    Deque<T,std::allocator<T>> d(std::from_range,vec);
    for (auto _ : state) {
        for(std::size_t i=0uz;i!=Length;++i){
            benchmark::DoNotOptimize(d.back());
        }
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void iteration(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    Deque<T,std::allocator<T>> d(std::from_range,vec);
    for (auto _ : state) {
        for(auto&&i:d){
            benchmark::DoNotOptimize(i);
        }
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void insert_1_front(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        d.insert(d.begin()+Length/3,0);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void insert_1_back(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        d.insert(d.begin()+Length/3*2,0);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void insert_3_front(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        d.insert(d.begin()+Length/3,Length,0);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void insert_3_back(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        d.insert(d.begin()+Length/3*2,Length,0);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void insert_4_front(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        d.insert(d.begin()+Length/3,vec.data(),vec.data()+Length);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void insert_4_back(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        d.insert(d.begin()+Length/3*2,vec.data(),vec.data()+Length);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void append_range(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        d.append_range(vec);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void prepend_range(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        d.prepend_range(vec);
        benchmark::DoNotOptimize(d);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void emplace_back_empty(benchmark::State& state) {
    for (auto _ : state) {
    Deque<T,std::allocator<T>> d{};
        for(std::size_t i = 0uz;i!=Length;++i){
            auto &&res =d.emplace_back(i); 
        benchmark::DoNotOptimize(res);
        }
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void emplace_front_empty(benchmark::State& state) {
    for (auto _ : state) {
    Deque<T,std::allocator<T>> d{};
        for(std::size_t i = 0uz;i!=Length;++i){
            auto &&res =d.emplace_front(i); 
        benchmark::DoNotOptimize(res);
        }
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void emplace_back(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        for(std::size_t i = 0uz;i!=Length;++i){
            auto &&res =d.emplace_back(i); 
        benchmark::DoNotOptimize(res);
        }
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void emplace_front(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        for(std::size_t i = 0uz;i!=Length;++i){
            auto &&res =d.emplace_front(i); 
        benchmark::DoNotOptimize(res);
        }
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void pop_back(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        for(std::size_t i = 0uz;i!=Length;++i){
            d.pop_back();
        }
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void pop_front(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        for(std::size_t i = 0uz;i!=Length;++i){
            d.pop_front();
        }
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void resize_extent(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
                state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        d.resize(Length*2);
    }
}

template <template<typename,typename> typename Deque,typename T, std::size_t Length>
void resize_shrink(benchmark::State& state) {
    auto vec = make_vector<T>(Length);
    for (auto _ : state) {
        state.PauseTiming();
        Deque<T,std::allocator<T>> d(std::from_range,vec);
        state.ResumeTiming();
        for (std::size_t i=0;i!=Length;++i){
            d.resize(Length-i-1);
        }
    }
}

#if defined(TEST_STD)
#define DEQUE std::deque
#else
#define DEQUE bizwen::deque
#endif

BENCHMARK(constructor_3<DEQUE,int,256>);
BENCHMARK(constructor_4<DEQUE,int,256>);
BENCHMARK(constructor_5_raw_ptr<DEQUE,int,256>);
BENCHMARK(constructor_5_vec_it<DEQUE,int,256>);
BENCHMARK(constructor_6<DEQUE,int,256>);
BENCHMARK(constructor_7_copy<DEQUE,int,256>);
BENCHMARK(at<DEQUE,int,256>);
BENCHMARK(operator_at<DEQUE,int,256>);
BENCHMARK(front<DEQUE,int,256>);
BENCHMARK(back<DEQUE,int,256>);
BENCHMARK(iteration<DEQUE,int,256>);
BENCHMARK(insert_1_front<DEQUE,int,256>);
BENCHMARK(insert_1_back<DEQUE,int,256>);
BENCHMARK(insert_3_front<DEQUE,int,256>);
BENCHMARK(insert_3_back<DEQUE,int,256>);
BENCHMARK(insert_4_front<DEQUE,int,256>);
BENCHMARK(insert_4_back<DEQUE,int,256>);
BENCHMARK(append_range<DEQUE,int,256>);
BENCHMARK(prepend_range<DEQUE,int,256>);
BENCHMARK(emplace_back_empty<DEQUE,int,256>);
BENCHMARK(emplace_front_empty<DEQUE,int,256>);
BENCHMARK(emplace_back<DEQUE,int,256>);
BENCHMARK(emplace_back_empty<DEQUE,int,256>);
BENCHMARK(pop_back<DEQUE,int,256>);
BENCHMARK(pop_front<DEQUE,int,256>);
BENCHMARK(resize_extent<DEQUE,int,256>);
BENCHMARK(resize_shrink<DEQUE,int,256>);

BENCHMARK(constructor_3<DEQUE,int,512>);
BENCHMARK(constructor_4<DEQUE,int,512>);
BENCHMARK(constructor_5_raw_ptr<DEQUE,int,512>);
BENCHMARK(constructor_5_vec_it<DEQUE,int,512>);
BENCHMARK(constructor_6<DEQUE,int,512>);
BENCHMARK(constructor_7_copy<DEQUE,int,512>);
BENCHMARK(at<DEQUE,int,512>);
BENCHMARK(operator_at<DEQUE,int,512>);
BENCHMARK(front<DEQUE,int,512>);
BENCHMARK(back<DEQUE,int,512>);
BENCHMARK(iteration<DEQUE,int,512>);
BENCHMARK(insert_1_front<DEQUE,int,512>);
BENCHMARK(insert_1_back<DEQUE,int,512>);
BENCHMARK(insert_3_front<DEQUE,int,512>);
BENCHMARK(insert_3_back<DEQUE,int,512>);
BENCHMARK(insert_4_front<DEQUE,int,512>);
BENCHMARK(insert_4_back<DEQUE,int,512>);
BENCHMARK(append_range<DEQUE,int,512>);
BENCHMARK(prepend_range<DEQUE,int,512>);
BENCHMARK(emplace_back_empty<DEQUE,int,512>);
BENCHMARK(emplace_front_empty<DEQUE,int,512>);
BENCHMARK(emplace_back<DEQUE,int,512>);
BENCHMARK(emplace_front_empty<DEQUE,int,512>);
BENCHMARK(pop_back<DEQUE,int,512>);
BENCHMARK(pop_front<DEQUE,int,512>);
BENCHMARK(resize_extent<DEQUE,int,512>);
BENCHMARK(resize_shrink<DEQUE,int,512>);

BENCHMARK(constructor_3<DEQUE,int,1024>);
BENCHMARK(constructor_4<DEQUE,int,1024>);
BENCHMARK(constructor_5_raw_ptr<DEQUE,int,1024>);
BENCHMARK(constructor_5_vec_it<DEQUE,int,1024>);
BENCHMARK(constructor_6<DEQUE,int,1024>);
BENCHMARK(constructor_7_copy<DEQUE,int,1024>);
BENCHMARK(at<DEQUE,int,1024>);
BENCHMARK(operator_at<DEQUE,int,1024>);
BENCHMARK(front<DEQUE,int,1024>);
BENCHMARK(back<DEQUE,int,1024>);
BENCHMARK(iteration<DEQUE,int,1024>);
BENCHMARK(insert_1_front<DEQUE,int,1024>);
BENCHMARK(insert_1_back<DEQUE,int,1024>);
BENCHMARK(insert_3_front<DEQUE,int,1024>);
BENCHMARK(insert_3_back<DEQUE,int,1024>);
BENCHMARK(insert_4_front<DEQUE,int,1024>);
BENCHMARK(insert_4_back<DEQUE,int,1024>);
BENCHMARK(append_range<DEQUE,int,1024>);
BENCHMARK(prepend_range<DEQUE,int,1024>);
BENCHMARK(emplace_back_empty<DEQUE,int,1024>);
BENCHMARK(emplace_front_empty<DEQUE,int,1024>);
BENCHMARK(emplace_back<DEQUE,int,1024>);
BENCHMARK(emplace_front_empty<DEQUE,int,1024>);
BENCHMARK(pop_back<DEQUE,int,1024>);
BENCHMARK(pop_front<DEQUE,int,1024>);
BENCHMARK(resize_extent<DEQUE,int,1024>);
BENCHMARK(resize_shrink<DEQUE,int,1024>);

BENCHMARK(constructor_3<DEQUE,int,2048>);
BENCHMARK(constructor_4<DEQUE,int,2048>);
BENCHMARK(constructor_5_raw_ptr<DEQUE,int,2048>);
BENCHMARK(constructor_5_vec_it<DEQUE,int,2048>);
BENCHMARK(constructor_6<DEQUE,int,2048>);
BENCHMARK(constructor_7_copy<DEQUE,int,2048>);
BENCHMARK(at<DEQUE,int,2048>);
BENCHMARK(operator_at<DEQUE,int,2048>);
BENCHMARK(front<DEQUE,int,2048>);
BENCHMARK(back<DEQUE,int,2048>);
BENCHMARK(iteration<DEQUE,int,2048>);
BENCHMARK(insert_1_front<DEQUE,int,2048>);
BENCHMARK(insert_1_back<DEQUE,int,2048>);
BENCHMARK(insert_3_front<DEQUE,int,2048>);
BENCHMARK(insert_3_back<DEQUE,int,2048>);
BENCHMARK(insert_4_front<DEQUE,int,2048>);
BENCHMARK(insert_4_back<DEQUE,int,2048>);
BENCHMARK(append_range<DEQUE,int,2048>);
BENCHMARK(prepend_range<DEQUE,int,2048>);
BENCHMARK(emplace_back_empty<DEQUE,int,2048>);
BENCHMARK(emplace_front_empty<DEQUE,int,2048>);
BENCHMARK(emplace_back<DEQUE,int,2048>);
BENCHMARK(emplace_front_empty<DEQUE,int,2048>);
BENCHMARK(pop_back<DEQUE,int,2048>);
BENCHMARK(pop_front<DEQUE,int,2048>);
BENCHMARK(resize_extent<DEQUE,int,2048>);
BENCHMARK(resize_shrink<DEQUE,int,2048>);

BENCHMARK_MAIN();