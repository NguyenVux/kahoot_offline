$(document).ready(function () {
    $("#toggle_mobile_menu").click(function () {
        $("#menu_mobile").toggle("block");
    });
    new Sortable(document.getElementById("list_question"), {
        animation: 150,
        dataIdAttr: "data-id",
        onEnd: function (evt) {
            let root = evt.target;
            console.log(root);
            $(root)
                .children()
                .each(function (i, v) {
                    $(v).attr("data-id", i);
                    $(v)
                        .find(`.number_question`)
                        .text(`Câu ${i + 1}`);
                });
        },
    });

    $(document).on("click", "#list_question .arrow", function () {
        console.log($(this).parent().find(".arrow"));
        $(this).parent().find(".arrow").toggleClass("hidden");
        $(this).parent().parent().find(".content_quest").toggle("hidden");
    });

    $(".add_quest").on("click", function () {
        let list_quest = $("#list_question");
        let stt = parseInt(list_quest.find(".ques_ans_comp").length) + 1;
        list_quest.append(`
        <div class="relative w-full cursor-move ques_ans_comp" data-id="${stt}">
                <a class="absolute -top-2 -right-2 px-2 py-1 border-2 text-white-100 font-bold hover:border-red-400 rounded-full remove_question" href="javascript:void(0)">
                    <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24"><path d="M3 6v18h18v-18h-18zm5 14c0 .552-.448 1-1 1s-1-.448-1-1v-10c0-.552.448-1 1-1s1 .448 1 1v10zm5 0c0 .552-.448 1-1 1s-1-.448-1-1v-10c0-.552.448-1 1-1s1 .448 1 1v10zm5 0c0 .552-.448 1-1 1s-1-.448-1-1v-10c0-.552.448-1 1-1s1 .448 1 1v10zm4-18v2h-20v-2h5.711c.9 0 1.631-1.099 1.631-2h5.315c0 .901.73 2 1.631 2h5.712z"/></svg>
                </a>
                <div class="px-10 my-4 py-6 bg-white rounded-lg shadow-xl">
                    <div class="flex justify-between items-center">
                        <span class="font-bold text-xl text-gray-600 number_question">Câu ${stt}</span>
                        <a class="px-2 py-1 text-black-100 font-bold arrow " href="javascript:void(0)">
                           <svg version="1.1" xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 129 129" xmlns:xlink="http://www.w3.org/1999/xlink" enable-background="new 0 0 129 129">
                                <g>
                                    <path d="m40.4,121.3c-0.8,0.8-1.8,1.2-2.9,1.2s-2.1-0.4-2.9-1.2c-1.6-1.6-1.6-4.2 0-5.8l51-51-51-51c-1.6-1.6-1.6-4.2 0-5.8 1.6-1.6 4.2-1.6 5.8,0l53.9,53.9c1.6,1.6 1.6,4.2 0,5.8l-53.9,53.9z"/>
                                </g>
                            </svg>
                        </a>
                        <a class="px-2 py-1 text-black-100 font-bold arrow hidden" href="javascript:void(0)">
                           <svg version="1.1" xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 129 129" xmlns:xlink="http://www.w3.org/1999/xlink" enable-background="new 0 0 129 129">
                                <g>
                                    <path d="m121.3,34.6c-1.6-1.6-4.2-1.6-5.8,0l-51,51.1-51.1-51.1c-1.6-1.6-4.2-1.6-5.8,0-1.6,1.6-1.6,4.2 0,5.8l53.9,53.9c0.8,0.8 1.8,1.2 2.9,1.2 1,0 2.1-0.4 2.9-1.2l53.9-53.9c1.7-1.6 1.7-4.2 0.1-5.8z"/>
                                </g>
                            </svg>
                        </a>
                    </div>
                    <div class="content_quest">
                        <div class="question mt-2">
                            <input name="question_${stt}" data_question="${stt}" class="border-b-2 p-2 my-4 focus:outline-none focus:border-b-4 focus:border-purple-600  w-full" placeholder="Câu hỏi ...">
                        </div>

                        <div class="answer mt-2 flex flex-col w-full">
                            <div class="flex items-center">
                                <span data-ans-id = "1">A.</span>
                                <input class="border-b-2 p-2 my-4 focus:outline-none focus:border-b-4 focus:border-purple-600 w-full" data-ans-question="${stt}" placeholder="Câu trả lời ...">
                                <input type="radio" class="form-radio h-5 w-5 checked:bg-purple-600" name="correct_ans_${stt}" data-correct-ans-question="${stt}">
                            </div>
                            <div class="flex items-center">
                                <span data-ans-id = "2">B.</span>
                                <input class="border-b-2 p-2 my-4 focus:outline-none focus:border-b-4 focus:border-purple-600 w-full" data-ans-question="${stt}" placeholder="Câu trả lời ...">
                                <input type="radio" class="form-radio h-5 w-5 checked:bg-purple-600" name="correct_ans_${stt}" data-correct-ans-question="${stt}">

                            </div>
                            <div class="flex items-center">
                                <span data-ans-id = "3">C.</span>
                                <input class="border-b-2 p-2 my-4 focus:outline-none focus:border-b-4 focus:border-purple-600 w-full" data-ans-question="${stt}" placeholder="Câu trả lời ...">
                                <input type="radio" class="form-radio h-5 w-5 checked:bg-purple-600" name="correct_ans_${stt}" data-correct-ans-question="${stt}">

                            </div>
                            <div class="flex items-center">
                                <span data-ans-id = "4">D.</span>
                                <input class="border-b-2 p-2 my-4 focus:outline-none focus:border-b-4 focus:border-purple-600 w-full" data-ans-question="${stt}" placeholder="Câu trả lời ...">
                                <input type="radio" class="form-radio h-5 w-5 checked:bg-purple-600" name="correct_ans_${stt}" data-correct-ans-question="${stt}">
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        `);
    });

    $("#list_question").on("click", ".remove_question", function (e) {
        $(this).parent().remove();
        let arrCurrentQuestion = $("#list_question").find(".ques_ans_comp");
        if (arrCurrentQuestion.length == 0) return;
        for (let i = 0; i < arrCurrentQuestion.length; i++) {
            $(arrCurrentQuestion[i]).attr("data-id", i + 1);
            $(arrCurrentQuestion[i]).find(
                ".number_question"
            )[0].innerHTML = `Câu ${i + 1}`;
            let text_quest = $(arrCurrentQuestion[i]).find(
                ".content_quest .question input"
            );
            $(text_quest).attr("name", `question_${i + 1}`);
            $(text_quest).attr("data_question", `${i + 1}`);
            let text_ans = $(arrCurrentQuestion[i])
                .find(".content_quest .answer")
                .children();
            // .children();
            let list_text_ans = $(text_ans).find("input[name]");
            let list_text_for_ques = $(text_ans).find(
                "input[data-ans-question]"
            );
            list_text_ans.each(function (index) {
                $(this).attr("name", `correct_ans_${i + 1}`);
                $(this).attr("data-correct-ans-question", `${i + 1}`);
            });
            list_text_for_ques.each(function (index) {
                $(this).attr("data-ans-question", `${i + 1}`);
            });
            // (list_text_ans);
        }
    });
});
