#ifndef MAALA_SLICING_HPP
#define MAALA_SLICING_HPP

#include <common.hpp>
#include <string>
#include <vector>

namespace maala {

   typedef size_t ind_t;
      typedef std::vector<ind_t> indVec; // index vector

      class SliceDesc1D {
      public:
         enum iterMode { range, list };
         SliceDesc1D()
            : m_indDef{ 0 }
            , m_iterMode{ list }
            , m_iterPos{ 0 }
         {}
         SliceDesc1D(indVec indDef, iterMode mode)
            : m_indDef{ indDef }
            , m_iterMode{ mode }
            , m_iterPos{ (range == mode) ? indDef[0] : 0 }
         {}
         ~SliceDesc1D() {}
         ind_t operator()() const { return (range == m_iterMode) ? m_iterPos : m_indDef[m_iterPos]; }
         bool inc();
         void setDef(indVec indDef, iterMode mode);
         void resetPos();
         size_t count() const { return (range == m_iterMode) ? m_indDef[1] - m_indDef[0] + 1 : m_indDef.size(); }
      private:
         indVec m_indDef;
         iterMode m_iterMode;
         ind_t m_iterPos;
      };

      struct SliceDesc2D {
      public:
         SliceDesc2D(indVec rowDef, SliceDesc1D::iterMode rowMode, indVec colDef, SliceDesc1D::iterMode colMode)
            : m_row{rowDef, rowMode}
            , m_col{ colDef, colMode}
         {}
         SliceDesc2D(SliceDesc1D row, SliceDesc1D col)
            : m_row{ row }
            , m_col{ col }
         {}
         SliceDesc1D m_row, m_col;
      };

} // namespace maala

#endif // ifndef MAALA_SLICING_HPP