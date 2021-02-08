/*
 * Copyright 2009-2017 Alibaba Cloud All rights reserved.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ALIBABACLOUD_VIDEOENHAN_MODEL_ERASEVIDEOLOGOREQUEST_H_
#define ALIBABACLOUD_VIDEOENHAN_MODEL_ERASEVIDEOLOGOREQUEST_H_

#include <string>
#include <vector>
#include <alibabacloud/core/RpcServiceRequest.h>
#include <alibabacloud/videoenhan/VideoenhanExport.h>

namespace AlibabaCloud
{
	namespace Videoenhan
	{
		namespace Model
		{
			class ALIBABACLOUD_VIDEOENHAN_EXPORT EraseVideoLogoRequest : public RpcServiceRequest
			{
			public:
				struct Boxes
				{
					float w;
					float h;
					float x;
					float y;
				};

			public:
				EraseVideoLogoRequest();
				~EraseVideoLogoRequest();

				std::vector<Boxes> getBoxes()const;
				void setBoxes(const std::vector<Boxes>& boxes);
				bool getAsync()const;
				void setAsync(bool async);
				std::string getVideoUrl()const;
				void setVideoUrl(const std::string& videoUrl);

            private:
				std::vector<Boxes> boxes_;
				bool async_;
				std::string videoUrl_;

			};
		}
	}
}
#endif // !ALIBABACLOUD_VIDEOENHAN_MODEL_ERASEVIDEOLOGOREQUEST_H_