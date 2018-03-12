#
#  Be sure to run `pod spec lint MgwSDKDemo1.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see http://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |s|


  s.name         = "MgwSDKDemo1"
  s.version      = "1.0"
  s.summary      = "iOS芒果玩客户端framework"

  s.description  = <<-DESC 
                 芒果玩接入SDK,用于cp快速接入SDK，使用Cocoapods
                 DESC

  s.homepage = "http://www.xingfeiinc.com"

  s.license      = "MIT"

  s.author             = { "duanzongwang" => "duanzongwang@xingfeiinc.com" }

  s.platform     = :ios

  s.source       = { :git => "https://github.com/heihuhei2013/MgwSDKDemo1.git", :tag => "#{s.version}" }

  s.source_files  = "**/*.{h,m}"
  
  s.frameworks =  "MgwSDK","StoreKit","CoreMotion","AdSupport","Photos","SystemConfiguration","Security","CoreGraphics","CoreTelephony","QuartzCore","UIKit"


end
