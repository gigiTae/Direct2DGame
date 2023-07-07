#pragma once

/*
 =============================게임 엔진에 대한 설명===============================

  게임오브젝트는 컴포넌트 기반으로 설계하고있다.

  가장 상단의 GameProcess가 Manager 와 D2dRenderer를 가진다
  Initalize를 통해서 미리 생성한 D2dRenderer를 가져오고 Manager들을 초기화한다.

  ============================게임 루프==========================
  1. timeManager 와 inputManager로 델타타입과 키입력을 처리한다.

  2. 물리 처리 단계에서는 간단한 게임의 물리 처리를 진행한다 
    물리처리는 한 프레임이 낮으면 여러번 호출된다. 
  3. 물리 처리 단계에서는 GameObject가 RigidBody와 연관이 있다.
 
  4. 충돌처리 단계에서는 오브젝트의 타입에 따라서 충돌을 처리하고 
    충돌처리는 각각 AABB, OBB, CC, CircleAndBox 처리가 있다.
    Collision 정보로는 상대방 게임 오브젝트와 충돌체를 반환한다. 
    x-> 충돌후의 물리적인 처리는 미구현

  5. 게임 오브젝트 업데이트 단계는 게임 오브젝트의 타입에의 순서대로 업데이트를 진행한다
   게임 오브젝트는 컴포넌트를 가지고 이 컴포넌트는 CALL_ORDER 에따라 순서대로 이벤트가 발생한다

  6. UIManager를 통해서 마우스에 관한 이벤트를 호출한다. 뎁스 구현 예정

  7. 랜더링은 D2D랜더러를 사용해서 랜더링한다. 
   랜더링함수 호출순서는 PreRender -> Render -> PostRender 순으로 호출한다
   디버그 정보는 F5를 사용해서 On/Off가 가능하다.

  8. 이벤트 지연처리는 오브젝트의 삭제, 생성, 씬 변경등의 이벤트들을 관리한다.
 
 =================================================================

 ========================== 엔진체계에 대한 고민 ===================================

 2023.07.03 오전 1:46
 부모 자식관계에 대해서 고민중이다 부모가 삭제되면 자식들도 모두 삭제해버리는 메커니즘이 맞겠지?
 맞는거 같다  부모와 자식은 종속적인 관계로서 작용해야하므로 처리를 그런방식으로 하자!
 하지만 자식이 삭제된다고 해서 부모는 삭제할 필요가 없어 보인다.

 2023.07.03 오후 12:13 
 부모 자식관계를 예외처리는 이제 랜더링에 관해서 작성해야할듯 다른것들의 예외처리는 거의 
 다 한거같음 

 2023.07.03 오후 5:23
 1.게임 오브젝트가 100이상이 넘어가면 충돌처리가 매우 오래걸려서 물리처리를 진행하는 업데이트를 해서
  게임프레임이 급격하게 감소한다. 
  2. 게임 오브젝트의 최상단의 부모만 씬에 등록하면 자식들은 자동으로 등록된다.      `   
  
 2023.07.03 오후 11:05
 이제부터 애니메이션 작업을 시작해야겠다 우선은 이미지 파일을 불러오고 화면에 출력해보자
 리소스들을 어디서 관리하는지에 대한 고민 RenderModule은 랜더링을 담당하는데 리소스들을 관리하고 
 들고있는게 맞는거 아니다 GameProcess에 ResourceManager가 모든 리소스를 관리하는 걸로 해보자

 2023.07.04 오후 12:07
 비트맵정보를 불러오기에 성공하였다! 
 리소스들은 D2DRenderer들이 관리하고 리소스 매니져에서도 같이 관리하면 괜찮을까? 리소스를 불러올때
 리소스 키값만 가지고 있으면 게임오브젝트는 랜더링이 비트맵을 출력가능하다. 
 애니메이션 컴포넌트를 만들어보자
 애니메이션 컴포넌트에는 필요한거 적어봐야할듯? 
 
 2023.07.04 오후 7:17
 SetTrasfrom 을 사용자에게 열지 말까? 그냥 오브젝트의 각도등을 알려주면 알아서 하면 설정해버리면 
 사용자 입장에서는 쉽게 사용이 가능하지 않나? 애니메이션 스프라이트는 어떤 방식으로 관리할까?
  진짜 고민인거는 게임오브젝트가 매니져들을 들고있어야 하는가이다 애니메이션도 가능할꺼같은데 음
  씬 변경, 오브젝트 추가하는것만 해결하면 괜찮아 질꺼같은데 우째해야할까 ??? 그냥 씬매니져주는것도 
  방법이긴한데 먼가 좀더 숨기는것이 좋아 보인다 나중에 추가하는 카메라매니져 ? D2D랜더로 해결가능할듯보임
  하지만 게임의 규모가 커짐에따라서 여러가지 매니져들이 추가되는데 이러한 구조를 계속해서 보장 가능한가?
  일단 SOUND는 전역으로 쓰는게 맞는거 같기는하다. 생각해보니 오브젝트 매니져를 통해서 계속해서 추가하는데 음
  이것도 고민해봐야할 문제인듯 하다 

  2023.07.05 오전 9:56
  D2D 랜더러가 점점더 무거워지는거 같다 분리를 할 필요가 있어보인다 ? 
  현재 이미지파일을 로드할떄 텍스처를 반환하는데 꼭 필요할까? 솔직히 필요없어 보임 
  다음으로 해야하는 일은 씬 변경과 씬 오브젝트 추가가 필요하다 음다음으로는 ? 
  충돌매니저 쪽 코드를 보완할 필요가 있어보인다 너무 가독성이 떨어져보임
  
  2023.7.5 19:54 gitae
  다음 엔진 목표는 어떤걸로 할까? 

  // 2023.7.6 0:02 gitae
  // 기본적인 카메라를 구현하였다. 확대,축소, 카메라 이동등
  // 여기서 추가적으로 카메라효과로 CCTV도 한번 구현해보자!

  // 2023.7.6 18:15 gitae
  // 한개 중요할 역할을 깨달았다 계속해서 게임오브젝트에 매니져들을 알려줬는데
  // 매니져의 업데이트 같은 오브젝트가 호출하면 안되는 함수들을 사용가능했었는데
  // const 키워드를 사용해서 접근이 불가능하게가 가능했다. 이 방법으로 매니져들을
  집합시켜서 모두 보내도 괜찮을꺼같음 다시 리팩토링이 필요한 시점이 왔다. 

  // 2023.7.7 0:03 gitae
  // 탬플릿을 사용해서 GetManager을 구현했는데  좀 ...... 많이 아닌거 같다 
  // 디버그도 힘들어지고 그냥 함수를 만드는 편이 좋아보인다 100배는 더.... 
  // 물론 엄청편하다는 장점이 있다 과연 reinterpret_cast 라는 위험한 친구를 쓰면서
  사용하는게 맞는지는 잘 모르겠다.

  // 2023.7.7 11:06 gitae
  // 결합도가 높아지는 거 같다. 게임오브젝트가 점점도 매니저에 의존하게 된다.
  
  // 2023.7.7 21:37 gitae
  // 게임오브젝트 타입에 UI 개체들은 자동으로 마우스 이벤트 함수를 호출하는 구조로 작성
  
====================================================================================

 */  