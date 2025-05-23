# 🐧 리눅스 파일 시스템 구조 (Linux File System Structure)

리눅스는 유닉스 파일 시스템(Unix File System, UFS)을 기반으로 발전해왔으며, 현재는 더욱 확장된 형태인 `ext4` 파일 시스템을 사용하고 있습니다.

---

## 🧱 유닉스 파일 시스템의 전체적인 구조

유닉스 기반의 파일 시스템은 다음과 같은 주요 블록들로 구성되어 있습니다:


### 📌 구성 요소

- **🔹 부트 블록 (Boot Block)**  
  - 파일 시스템의 시작부 (일반적으로 첫 번째 섹터)
  - 부트스트랩 코드(bootstrap code) 저장

- **🔹 슈퍼 블록 (Super Block)**  
  - 파일 시스템 전체의 메타데이터 저장
  - 예: 블록 수, 사용 가능한 i-node 수, 비트맵 등

- **🔹 i-리스트 (i-list)**  
  - 모든 i-노드들의 리스트
  - 각 파일의 메타데이터(i-node 정보)를 포함

- **🔹 데이터 블록 (Data Blocks)**  
  - 실제 파일의 데이터 저장 공간

---

## 📂 ext 파일 시스템 (Extended File System)

리눅스는 유닉스 파일 시스템을 기반으로 하여 자체적으로 **ext (extended)** 파일 시스템을 발전시켰습니다.

### 🧬 주요 ext 파일 시스템 버전

| 버전  | 설명                                      |
|-------|-------------------------------------------|
| ext   | 초기 버전, 제한된 기능과 성능             |
| ext2  | 저널링 없음, 기본적인 기능 제공           |
| ext3  | 저널링 추가, 안정성과 성능 향상           |
| **ext4** | 최신 표준, 대용량 파일과 고성능 지원      |

---

## 🚀 ext4 파일 시스템 특징

`ext4`는 현재 대부분의 리눅스 배포판에서 기본 파일 시스템으로 사용됩니다.

- ✅ **1EB (엑사바이트)** 이상의 대용량 볼륨 지원  
  *(1EB = 1024 × 1024 TB)*
- ✅ **16TB 이상의 단일 파일** 저장 가능
- ✅ 향상된 성능, 저널링 기능, 디스크 오류 복구 기능 등 제공

---

> 📚 **참고**: ext4는 향후 Btrfs나 XFS 같은 파일 시스템으로 대체될 가능성도 있지만, 여전히 광범위하게 사용되고 있는 안정적인 표준입니다.

# 📌 i-노드 (i-node)

i-노드는 리눅스 및 유닉스 파일 시스템에서 **파일의 모든 메타데이터**를 저장하는 구조체입니다.  
파일의 실제 내용은 데이터 블록에 저장되며, i-노드는 그 파일에 대한 **정보와 위치**를 추적합니다.

---

## 📁 i-노드의 개념

- 하나의 **파일 또는 디렉토리**는 하나의 **i-노드**를 가집니다.
- i-노드는 해당 파일에 대한 **속성 정보**와 **데이터 블록의 주소**를 포함합니다.

---

## 🔍 i-노드에 저장되는 정보

| 항목                   | 설명                                                      |
|------------------------|-----------------------------------------------------------|
| 📄 파일 타입           | 일반 파일, 디렉터리, 블록 장치 파일, 문자 장치 파일 등  |
| 📏 파일 크기           | 바이트 단위의 크기 정보                                   |
| 🔐 접근 권한           | 읽기/쓰기/실행 권한 (예: `rwxr-xr--`)                     |
| 👤 파일 소유자 및 그룹 | 사용자 ID (UID), 그룹 ID (GID)                           |
| 🕒 접근/수정 시간       | 마지막 접근 시간, 마지막 수정 시간 등 타임스탬프          |
| 🧭 데이터 블록 포인터  | 파일 내용이 저장된 데이터 블록의 위치(주소)              |

---

## 🧬 i-노드와 데이터 블록의 관계

i-노드는 데이터 블록의 주소를 알고 있을 뿐, 실제 내용을 직접 저장하지 않습니다.  
즉, **i-노드는 “파일이 어디에 있는지”를 알려주는 정보 저장소**입니다.

# 📂 디렉터리 리스트 함수 (Directory Listing in C)

리눅스/유닉스 환경에서 디렉터리 내의 파일 목록을 확인하려면 C 언어에서 다음과 같은 함수를 사용합니다:

---

## 📘 주요 함수

### 🔹 `opendir()`

- 디렉터리를 여는 함수
- 성공 시 디렉터리를 가리키는 **`DIR *` 포인터**를 반환
- 실패 시 `NULL`을 반환

```c
#include <sys/types.h>
#include <dirent.h>

DIR *opendir(const char *path);

