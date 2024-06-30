#pragma once

//内存管理
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = NULL; } }
