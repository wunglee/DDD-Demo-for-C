#ifndef C2CPLATFORM_LIBRARY_STRING_STRING_HELPER_H
#define C2CPLATFORM_LIBRARY_STRING_STRING_HELPER_H

#include <set>
#include <string>
#include <vector>

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <unistd.h>

static const char DIVIDER[] = "|||";

/**
 * @fn 利用分隔符切割字符串到vector中
 *
 * @param sContent [in]要被字符串
 * @param sDivider [in]分割字符
 * @param vecStr   [out]分割好的vector
 *
 * @return uint32_t 切割出的子串数量=vecStr.size()
 *
 */
static inline uint32_t SplitStringIntoVector(
    const char* sContent, const char* sDivider, std::vector<std::string>& vecStr) {
  char* sNewContent = new char[strlen(sContent) + 1];
  snprintf(sNewContent, strlen(sContent) + 1, "%s", sContent);

  char* pStart = sNewContent;
  char* pEnd = sNewContent;

  std::string strContent;

  pEnd = strstr(sNewContent, sDivider);
  if (pEnd == NULL && strlen(sNewContent) > 0) {
    strContent = pStart;  // get the last one;
    vecStr.push_back(strContent);
  }

  while (pEnd) {
    *pEnd = '\0';
    strContent = pStart;
    vecStr.push_back(strContent);

    pStart = pEnd + strlen(sDivider);
    if ((*pStart) == '\0') {
      break;
    }

    pEnd = strstr(pStart, sDivider);

    if (pEnd == NULL) {
      strContent = pStart;  // get the last one;
      vecStr.push_back(strContent);
    }
  }

  delete[] sNewContent;

  return vecStr.size();
}

#endif
