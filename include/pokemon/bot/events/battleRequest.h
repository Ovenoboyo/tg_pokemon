#ifndef BATTLEREQUEST_H
#define BATTLEREQUEST_H

#include <string>
#include <unordered_map>

/**
 * @brief Holds pending battle requests
 *
 */
inline std::unordered_map<int32_t, int32_t> allRequests;

void RegisterRequest(int32_t p2, int32_t p1);
void DeregisterRequest(int32_t p2);

#endif
