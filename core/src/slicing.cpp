#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <common.hpp>
#include <slicing.hpp>

namespace maala {

   bool SliceDesc1D::inc() {
      if (range == m_iterMode) {
         if (m_iterPos < m_indDef[1]) {
            m_iterPos++;
            return true;
         }
         else {
            return false;
         }
      }
      else { // list == m_iterMode
         if ((m_iterPos + 1) < m_indDef.size()) {
            m_iterPos++;
            return true;
         }
         else {
            return false;
         }
      }
   }

   void SliceDesc1D::setDef(indVec indDef, SliceDesc1D::iterMode mode)
   {
      m_indDef = indDef;
      m_iterMode = mode;
      resetPos();
   }

   void SliceDesc1D::resetPos()
   {
      m_iterPos = (range == m_iterMode) ? m_indDef[0] : 0;
   }

} // namespace maala