//
// Created by MORIMOTO on 2017/12/17.
//

#ifndef MODERNCPP_FUNCTIONTEMPLATE_H
#define MODERNCPP_FUNCTIONTEMPLATE_H

#include <type_traits>
namespace func {
//   template <typename T1, typename T2>
//   std::common_type_t<T1, T2> max(T1 a, T2 b)
//   {
//      return b < a ? a : b;
//   }
//
   
   template <typename T1, typename T2>
   auto max(T1 a, T2 b) -> std::decay_t<decltype(true ? a : b)>
   {
      return b < a ? a : b;
   }
   
}
#endif //MODERNCPP_FUNCTIONTEMPLATE_H
