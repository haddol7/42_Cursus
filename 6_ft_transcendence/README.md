# user API

### /user/
* GET : 사용자 프로필 조회 (쿼리 요청)
    + /user/?user_name=<user_name>
    + Response (json)
        - {
             "user_name":string,
             "memo":string,
             "image_url":string"
          }
    + Error
        - 'user_name' 쿼리가 없을 경우, 400 BAD_REQUEST
        - 'user_name' 을 찾지 못할 경우, 404 NOT_FOUND
        - jwt 검증 실패시, 401 UNAUTHORIZED
        - 그 외는 500 INTERNAL SERVER ERROR
###
* PUT : 사용자 프로필 수정
    + body로 'user_name', 'memo', 'image_url' 를 받습니다.
    + 프로필 이미지 수정 요청의 경우, "Content-Type: multipart/form-data" 가 필요합니다. 
    + Response (json) : GET요청과 동일합니다.
    + Error
        - body 인자가 잘못된 경우, 400 BAD_REQUEST
        - jwt 검증 실패시, 401 UNAUTHORIZED
        - 그 외는 500 INTERNAL SERVER ERROR
###
### /user/friend
* GET : 사용자 친구 목록 조회
    + Response (json)
        - { 
            "user_name":string1
            "user_name":string2
            ...
        }
    + Error
        - jwt 검증 실패시, 401 UNAUTHORIZED
        - 그 외는 500 INTERNAL SERVER ERROR
###
* POST : 친구 추가
    + body로 'user_name'을 받습니다.
    + Error
        - user_name이 없을 시, 400
        - 친구를 찾을 수 없을 경우, 404
        - 자기 자신을 친구로 추가할 경우, 400
        - 이미 친구로 추가된 경우, 400
        - jwt 검증 실패시, 401 UNAUTHORIZED
        - 그 외는 500 INTERNAL SERVER ERROR


### /user/dashboard
* GET : 대시보드를 가져옵니다.
    + Response (json)
        - {
            "win_cnt":number
            "total_cnt":number
            "top_ranking" Profile list
                (
                    "user_name":string
                    "profile_url":string
                    "win_cnt":string
                    "total_cnt":string
                )
        }
    + Error:
        - jwt 검증 실패시, 401 UNAUTHORIZED
        - 그 외는 500 INTERNAL SERVER ERROR

### /_internal/user
* GET : 'user_id(int)'로 쿼리 요청시 'user_name'을 반환합니다.
* POST : 사용자 로그인시 프로필을 생성합니다.
    + body로 'user_id', 'user_name'을 받습니다.

### /_internal/dashboard
* POST : 게임 종료 시 게임 서버로 부터 유저의 승패 여부를 받습니다.
    + body로 'user_id', 'result'(='win' or 'lose')를 받습니다.
