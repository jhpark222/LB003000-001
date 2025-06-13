#include <assert.h>
#include <stdio.h>

extern int create_user_account(bool isAdmin, const char *username);
extern bool update_username(int user_id, const char *new_name);
extern bool is_admin(int user_id);

// 취약점 테스트 함수
void test_privilege_escalation() {
    int user_id = create_user_account(false, "normal_user");
    assert(!is_admin(user_id));

    // 공격: username 필드 넘쳐서 isAdmin 플래그 덮어쓰기 시도
    char exploit[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"  // 39자
                     "\x01";  // isAdmin = true로 만들기 위한 조작

    update_username(user_id, exploit);

    // 관리자 권한 상승 여부 확인
    if (is_admin(user_id)) {
        printf("[!] 권한 상승 성공 - 취약점 존재\n");
    } else {
        printf("[+] 권한 상승 실패 - 취약점 없음\n");
    }
}
