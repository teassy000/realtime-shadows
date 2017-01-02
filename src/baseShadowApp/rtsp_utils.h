#pragma once

#define rts_safeDelete(x) {if(x) {delete(x); (x) = nullptr;}}
#define rts_safeRelease(x) {if(x) {(x)->Release(); (x) = nullptr;}}
